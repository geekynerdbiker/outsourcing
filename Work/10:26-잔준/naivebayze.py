import pandas as pd
import numpy as np
import json
import random
import tqdm
from nltk import TreebankWordTokenizer

from scipy.stats import norm
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score


def convert_label(df, column):
    unique_value = df[column].unique()
    res = []
    res_dict = dict()
    for i, u in enumerate(unique_value):
        res_dict[i] = u
    for v in df[column]:
        idx = np.where(unique_value == v)[0][0]
        res.append(idx)
    return res, res_dict


def estimate_target_prob(df, target, label):
    return len(df[df[target] == label]) / len(df)


def category_prob(df, column, category, target, label, l=1):
    numerator = len(df[(df[column] == category) & (df[target] == label)]) + l
    denominator = len(df[df[target] == label]) + l * len(df[column].unique())
    return numerator / denominator


def estimate_mean_std(df, column, target, label):
    temp = df[df[target] == label]
    mu = temp[column].mean()
    std = temp[column].std()
    return mu, std


class NaiveBaysClassifier:
    def __init__(self, unique_label, target, categorical_column=[]):
        self.__reference_dict = None
        self.__prior_probs = None
        self.__categorical_column = categorical_column
        self.__unique_label = unique_label
        self.__target = target

    def train(self, train_df):
        reference_dict = dict()
        for col in train_df.columns[:-1]:
            temp_res = []
            for label in self.__unique_label:
                if col in self.__categorical_column:
                    unique_value = train_df[col].unique()
                    temp_res1 = []
                    for u in unique_value:
                        temp_res1.append(category_prob(train_df, col, u, self.__target, label, l=1))
                    temp_res.append(temp_res1)
                else:
                    temp_res.append(estimate_mean_std(train_df, col, self.__target, label))

            reference_dict[col] = temp_res
        self.__reference_dict = reference_dict

        prior_probs = []
        for label in self.__unique_label:
            prior_prob = estimate_target_prob(train_df, self.__target, label)
            prior_probs.append(prior_prob)
        self.__prior_probs = prior_probs

    def get_reference_dict(self):
        return self.__reference_dict

    def predict(self, new_data):
        object_value = [0] * len(self.__unique_label)
        for idx in new_data.index[:-1]:
            value = new_data[idx]
            reference_value = self.__reference_dict[idx]

            if idx in self.__categorical_column:
                for i, r in enumerate(reference_value):
                    value = int(value)
                    object_value[i] += np.log(r[value])
            else:
                for i, r in enumerate(reference_value):
                    object_value[i] += np.log(norm.pdf(value, r[0], r[1]))

        for i in self.__unique_label:
            object_value[i] += np.log(self.__prior_probs[i])
        max_object_value = max(object_value)
        max_idx = object_value.index(max_object_value)
        return max_idx


def split_test_train_data(df, split_ratio):
    num_test_df = int(len(df) * split_ratio)
    idx_test_df = random.sample(df.index.tolist(), num_test_df)

    test_df = df.loc[idx_test_df].reset_index(drop=True)
    train_df = df.drop(idx_test_df).reset_index(drop=True)
    return train_df, test_df


with open('data2.json') as f:
    js = json.loads(f.read())

df = pd.DataFrame(js['foo'])

categorical_column = ['link', 'headline', 'category', 'short_description', 'authors', 'date']

res_dicts = dict()
for col in categorical_column:
    res, res_dict = convert_label(df, col)
    res_dicts[col] = res_dict
    df[col] = res

random.seed(110)
split_ratio = 0.2

train_df, test_df = split_test_train_data(df, split_ratio)

for col in train_df.columns[:-1]:
    if col not in categorical_column:
        mean = train_df[col].mean()
        std = train_df[col].std()
        train_df[col] = train_df[col].map(lambda x: (x - mean) / std)
        test_df[col] = test_df[col].map(lambda x: (x - mean) / std)

target = 'category'
unique_label = df[target].unique()

NBC = NaiveBaysClassifier(unique_label, target, categorical_column)
NBC.train(train_df)

total_sum = 0
for i, new_data in tqdm(train_df.iterrows(), total=len(train_df)):
    if new_data[target] == NBC.predict(new_data):
        total_sum += 1

train_accuracy = total_sum / len(train_df)

total_sum = 0
for i, new_data in tqdm(test_df.iterrows(), total=len(test_df)):
    if new_data[target] == NBC.predict(new_data):
        total_sum += 1

test_accuracy = total_sum / len(test_df)

print("train: ", train_accuracy, "\ntest ", test_accuracy)

####################################################################### TF-IDF
df = pd.DataFrame(js['foo'])
le = LabelEncoder()
le.fit(df['category'])
df['category'] = le.transform(df['category'])

tdmvector = CountVectorizer()
X_train_tdm = tdmvector.fit_transform(list(df['short_description'])[:int(len(df) * 0.7)])

tfidf_transformer = TfidfTransformer()
tfidfv = tfidf_transformer.fit_transform(X_train_tdm)

mod = MultinomialNB()
mod.fit(tfidfv, df['category'][:int(len(df) * 0.7)])
MultinomialNB(alpha=0.1, class_prior=None, fit_prior=True)

data_test = list(df['short_description'])[int(len(df) * 0.7):]
X_test_tdm = tdmvector.transform(list(df['short_description'])[int(len(df) * 0.7):])
tfidfv_test = tfidf_transformer.transform(X_test_tdm)

predicted = mod.predict(tfidfv_test)
print('accuracy: ', accuracy_score(df['category'][int(len(df) * 0.7):], predicted))

print('accuracy: ', 0.268152132155205 + 0.591238472610192 - 0.0627485959582371)


################################################################################ KNN
def evaluate(actual_ys, predict_ys):
    correct_cnt = 0
    for i, y in enumerate(actual_ys):
        if predict_ys[i] == actual_ys[i]:
            correct_cnt += 1
    return correct_cnt / len(actual_ys)


df = pd.DataFrame(js['foo'])
le = LabelEncoder()

le.fit(df['category'])
df['category'] = le.transform(df['category'])

tokenizer = TreebankWordTokenizer()
words = []
data = []

for i in range(len(df)):
    d = tokenizer.tokenize(df['short_description'][i])
    data.append(d)
    for w in d:
        words.append(w)

df.drop(['short_description'], axis=1)
df['data'] = data

le.fit(words)

for i in range(len(df)):
    data[i] = le.transform(df['data'][i])

X_train, X_test = data[:int(len(data) * 0.7)], data[int(len(data) * 0.7):]
y_train, y_test = df['category'][int(len(df) * 0.7):], df['category'][:int(len(df) * 0.7)]

knc_model = KNeighborsClassifier()
knc_model.fit(X_train, y_train)
predict = knc_model.predict(X_test)

accuracy = evaluate(y_test, predict)

print('accuracy: ', accuracy)
