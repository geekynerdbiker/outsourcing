#############################################################
# TextBlob
#############################################################
from textblob import TextBlob
from textblob.classifiers import NaiveBayesClassifier
import textblob
import pandas as pd

import nltk
import ssl

try:
    _create_unverified_https_context = ssl._create_unverified_context
except AttributeError:
    pass
else:
    ssl._create_default_https_context = _create_unverified_https_context

nltk.download('punkt')
nltk.download('stopwords')

data = pd.read_csv("Tweets.csv")

text = data['text']
sentiment = data['airline_sentiment']

data = []
for t, s in zip(text, sentiment):
    if s == 'neutral':
        s = 'neu'
        data.append((t, s))
    elif s == 'positive':
        s = 'pos'
        data.append((t, s))
    elif s == 'negative':
        s = 'neg'
        data.append((t, s))

train = data[:int(len(data) * 0.7)]
test = data[int(len(data) * 0.7):]

cl = NaiveBayesClassifier(train)

cl.classify("The apples are good")
cl.classify("I don't like you.")

blob = TextBlob("The beer was nice. "
                "But the hangover was horrible.",
                classifier=cl)
blob.classify()

acc = cl.accuracy(test)
print("Accuracy of TextBlob: ", acc)

#############################################################
# scikit-learn
#############################################################

from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.pipeline import Pipeline
from sklearn.linear_model import LogisticRegression
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import GridSearchCV

import numpy as np
import re
from nltk.stem.porter import PorterStemmer
from nltk.corpus import stopwords

porter = PorterStemmer()
stop = stopwords.words('english')


def preprocessor(text):
    text = re.sub('<[^>]*>', '', text)
    emoticons = re.findall('(?::|;|=)(?:-)?(?:\)|\(|D|P)',
                           text)
    text = (re.sub('[\W]+', ' ', text.lower()) +
            ' '.join(emoticons).replace('-', ''))
    return text


def tokenizer(text):
    text = re.sub('<[^>]*>', '', text)
    emoticons = re.findall('(?::|;|=)(?:-)?(?:\)|\(|D|P)', text.lower())
    text = re.sub('[\W]+', ' ', text.lower()) + \
           ' '.join(emoticons).replace('-', '')
    tokenized = [w for w in text.split() if w not in stop]
    return tokenized


def tokenizer_porter(text):
    return [porter.stem(word) for word in text.split()]


count = CountVectorizer()
docs = np.array([
    'The apples are good',
    "I don't like you.",
    'The beer was nice., But the hangover was horrible.'])
bag = count.fit_transform(docs)

new_text = []
new_sentiment = []

for t, s in zip(text, sentiment):
    if s == 'positive' or s == 'negative':
        new_text.append(preprocessor(t))

for s in sentiment:
    if s == 'positive':
        new_sentiment.append(1)
    elif s == 'negative':
        new_sentiment.append(0)

tfidf = TfidfTransformer(use_idf=True, norm='l2', smooth_idf=True)
np.set_printoptions(precision=2)
print(tfidf.fit_transform(count.fit_transform(docs)).toarray())

x_train = new_text[:int(len(new_text) * 0.7)]
y_train = new_sentiment[:int(len(new_sentiment) * 0.7)]
x_test = new_text[int(len(new_text) * 0.7):]
y_test = new_sentiment[int(len(new_sentiment) * 0.7):]

tfidf = TfidfVectorizer(strip_accents=None,
                        lowercase=False,
                        preprocessor=None)

param_grid = [{'vect__ngram_range': [(1, 1)],
               'vect__stop_words': [stop, None],
               'vect__tokenizer': [tokenizer, tokenizer_porter],
               'clf__penalty': ['l1', 'l2'],
               'clf__C': [1.0, 10.0, 100.0]},
              {'vect__ngram_range': [(1, 1)],
               'vect__stop_words': [stop, None],
               'vect__tokenizer': [tokenizer, tokenizer_porter],
               'vect__use_idf': [False],
               'vect__norm': [None],
               'clf__penalty': ['l1', 'l2'],
               'clf__C': [1.0, 10.0, 100.0]},
              ]

lr_tfidf = Pipeline([('vect', tfidf),
                     ('clf', LogisticRegression(random_state=0, solver='liblinear'))])

gs_lr_tfidf = GridSearchCV(lr_tfidf, param_grid,
                           scoring='accuracy',
                           cv=5,
                           n_jobs=-1)

gs_lr_tfidf.fit(x_train, y_train)

clf = gs_lr_tfidf.best_estimator_
print("Accuracy of sklearn: ", clf.score(x_test, y_test))
