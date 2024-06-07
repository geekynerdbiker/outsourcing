import json
import numpy as np
from typing import Dict
from tqdm import tqdm
from collections import Counter

import nltk
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize

from sklearn.model_selection import train_test_split
import pandas as pd

nltk.download('punkt')
nltk.download('averaged_perceptron_tagger')
nltk.download('stopwords')


class NLDataset:
    def __init__(self):
        self.number_of_features = 4415
        self.word2idx: Dict[str, int]
        self.label2idx = {label: idx for idx,
                          label in enumerate([0, 1, 2, 3, 4, 5])}

        self.number_of_labels = len(self.label2idx)

        train_data, test_data, inference_data = self._load_data()
        self.X_train, self.y_train = self._data_tokenization(
            train_data, data_type='train')
        self.X_test, self.y_test = self._data_tokenization(
            test_data, data_type='test')
        self.X_inference = self._data_tokenization(
            inference_data, data_type='inference')

    def _load_data(self):

        train = pd.read_csv('data/train.csv')
        test = pd.read_csv('data/validation.csv')
        inference = pd.read_csv('data/test.csv')

        train_data = train.to_dict(orient='records')
        test_data = test.to_dict(orient='records')
        inference_data = inference['Lyric'].to_list()

        return train_data, test_data, inference_data

    def _data_tokenization(self, data, data_type='train'):
        extract_specific_tags = ['NN', 'NNS', 'NNP',
                                 'NNPS', 'VB', 'VBD', 'VBG', 'VBN', 'VBP', 'VBZ']
        stop_words = set(stopwords.words('english'))

        tokenized_data = []
        targets = []
        if data_type == 'train':
            all_tokens = []

        if data_type != 'inference':
            for d in tqdm(data, desc='Tokenizing...'):
                Lyric = d['Lyric']
                pos_tokens = nltk.pos_tag(word_tokenize(Lyric.lower()))
                tokenized_Lyric = [token[0] for token in pos_tokens if (
                    token[1] in extract_specific_tags) and (token[0] not in stop_words)]
                tokenized_data.append(tokenized_Lyric)

                targets.append(self.label2idx[d['Emotion']])

                if data_type == 'train':
                    all_tokens.extend(tokenized_Lyric)
        else:
            for d in tqdm(data, desc='Tokenizing...'):
                Lyric = d
                pos_tokens = nltk.pos_tag(word_tokenize(Lyric.lower()))
                tokenized_Lyric = [token[0] for token in pos_tokens if (
                    token[1] in extract_specific_tags) and (token[0] not in stop_words)]
                tokenized_data.append(tokenized_Lyric)

        if data_type != 'inference':
            targets = np.array(targets).reshape(len(targets),)

        if data_type == 'train':
            common_words = Counter(all_tokens).most_common(
                self.number_of_features)
            self.word2idx = {word: idx for idx,
                             (word, _) in enumerate(common_words)}

        if data_type != 'inference':
            return tokenized_data, targets
        else:
            return tokenized_data

    def sequences_to_matrix(self, data, mode='binary'):
        """
        Convert a list of sequences into a Numpy matrix.

        Parameters:
        - data: list of sequences
            (a sequence is a list of word tokens).
        - mode: one of "binary", "count"

        Process:
        1. Drop words not registered in the word2idx dictionary from the data
        2. Convert data to a binary/count vector that has dimension of the word2idx dictionary
            2.1. Binary: If a word exists in the data, 1 is assigned to the index otherwise 0 is assigned.
            2.2. Count: The number of words is assigned to the corresponding index.

        example)
            input: [['cups', 'flour'], ['replace', 'flour', 'replace', 'keyboard', 'minutes'], ['prefer', 'windows', 'mac', 'mac', 'keyboard', 'mac']]
            output: 
                - binary
                    [[0., 1., 0., 0., 1., 0., 0., 0.],
                    [0., 1., 1., 1., 0., 1., 0., 0.],
                    [1., 0., 0., 1., 0., 0., 1., 1.]]
                - count
                    [[0., 1., 0., 0., 1., 0., 0., 0.],
                    [0., 1., 2., 1., 0., 1., 0., 0.],
                    [3., 0., 0., 1., 0., 0., 1., 1.]]

        Returns:
        - A Numpy matrix.
        """
        new_data = list()
        if mode == 'binary':
            for d in tqdm(data, desc='Calculate_Binary...'):
                ############################################## EDIT ################################################
                dropped_sequence = [1 if token in d else 0 for token in list(self.word2idx.keys())]
                new_data.append(dropped_sequence)
                ####################################################################################################
        elif mode == 'count':
            for d in tqdm(data, desc='Calculate_Count...'):
                ############################################## EDIT ################################################
                dropped_sequence = [d.count(token) if token in d else 0 for token in list(self.word2idx.keys())]
                new_data.append(dropped_sequence)
                ####################################################################################################
        return np.array(new_data, dtype=np.float32)

    def to_categorical(self, data):
        mapping = np.eye(len(self.label2idx))
        data = [mapping[d] for d in data]
        return np.array(data, dtype=np.float32)


if __name__ == '__main__':

    dataset = NLDataset()

    binary_x_train = dataset.sequences_to_matrix(
        dataset.X_train, mode='binary')
    binary_x_test = dataset.sequences_to_matrix(dataset.X_test, mode='binary')
    count_x_train = dataset.sequences_to_matrix(dataset.X_train, mode='count')
    count_x_test = dataset.sequences_to_matrix(dataset.X_test, mode='count')
    y_train = dataset.to_categorical(dataset.y_train)
    y_test = dataset.to_categorical(dataset.y_test)

    np.savez('data/your_processed_dataset',
             binary_x_train=binary_x_train,
             binary_x_test=binary_x_test,
             count_x_train=count_x_train,
             count_x_test=count_x_test,
             y_train=y_train,
             y_test=y_test
             )

    your_dataset = np.load('data/your_processed_dataset.npz')
    answer_dataset = np.load('data/answer_processed_dataset.npz')

    print("{:<15}".format("binary_x_train:"), np.equal(
        your_dataset['binary_x_train'], answer_dataset['binary_x_train']).all())
    print("{:<15}".format("binary_x_test:"), np.equal(
        your_dataset['binary_x_test'], answer_dataset['binary_x_test']).all())
    print("{:<15}".format("count_x_train:"), np.equal(
        your_dataset['count_x_train'], answer_dataset['count_x_train']).all())
    print("{:<15}".format("count_x_test:"), np.equal(
        your_dataset['count_x_test'], answer_dataset['count_x_test']).all())
    print("{:<15}".format("y_train:"), np.equal(
        your_dataset['y_train'], answer_dataset['y_train']).all())
    print("{:<15}".format("y_test:"), np.equal(
        your_dataset['y_test'], answer_dataset['y_test']).all())
