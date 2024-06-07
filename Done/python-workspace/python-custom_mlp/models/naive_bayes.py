import pandas as pd
from sklearn.naive_bayes import MultinomialNB
from utils import calculate_score
import sys

sys.path.append("..")


class NaiveBayes:
    def __init__(self, dataset):
        ############################################## EDIT ################################################
        self.X_train = dataset.sequences_to_matrix(dataset.X_train, mode='count')
        self.X_test = dataset.sequences_to_matrix(dataset.X_test, mode='count')
        self.X_inference = dataset.sequences_to_matrix(dataset.X_inference, mode='count')
        self.y_train = dataset.y_train
        self.y_test = dataset.y_test
        ####################################################################################################
        self.classifier = MultinomialNB()

    def train(self):
        self.classifier.fit(self.X_train, self.y_train)

    def test(self):
        y_test_pred = self.classifier.predict(self.X_test)
        result = calculate_score(self.y_test, y_test_pred)
        print(f'Test Accuracy for Naive Bayes is {result["accuracy"][0]:.4f}')
        return result

    def inference(self):
        y_pred = self.classifier.predict(self.X_inference)

        test_df = pd.read_csv('data/test.csv')
        test_df['Emotion'] = y_pred
        output_df = test_df[['id', 'Emotion']]
        output_df.to_csv(f'output/naive_bayes_predictions.csv', index=False)

    def run(self):
        print("-------------------------Naive Bayes-------------------------\n", end='')
        self.train()
        self.inference()
        return self.test()
