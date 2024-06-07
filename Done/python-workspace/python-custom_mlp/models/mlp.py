import pandas as pd
from keras import layers
from keras import models
import numpy as np
from utils import calculate_score
import sys

sys.path.append("..")


class MLP:
    def __init__(self, config, dataset):
        self.config = config
        ############################################## EDIT ################################################
        self.X_train = dataset.sequences_to_matrix(dataset.X_train, mode='binary')
        self.X_test = dataset.sequences_to_matrix(dataset.X_test, mode='binary')
        self.X_inference = dataset.sequences_to_matrix(dataset.X_inference, mode='binary')
        self.y_train = dataset.to_categorical(dataset.y_train)
        self.y_test = dataset.to_categorical(dataset.y_test)
        ####################################################################################################

        self.classifier = models.Sequential()

    def train(self):
        self.classifier.fit(self.X_train,
                            self.y_train,
                            epochs=self.config.epochs,
                            validation_data=(self.X_test, self.y_test)
                            )

    def test(self):
        ############################################## EDIT ################################################
        y_test_pred = np.argmax(self.classifier.predict(self.X_test), axis=1)
        ####################################################################################################
        result = calculate_score(self.y_test, y_test_pred)
        print(f'Test Accuracy for MLP is {result["accuracy"][0]:.4f}')
        return result

    def inference(self):
        ############################################## EDIT ################################################
        y_pred = np.argmax(self.classifier.predict(self.X_inference), axis=1)
        ####################################################################################################
        test_df = pd.read_csv('data/test.csv')
        test_df['Emotion'] = y_pred
        output_df = test_df[['id', 'Emotion']]
        output_df.to_csv(f'output/mlp_predictions.csv', index=False)

    def run(self):
        """
       Add a layer to the neural network model and compile it.

       Layer1: Fully connected layer with ReLU activation function
               output shape: hidden size defined in config, Specify input shape
       Layer2: Fully connected layer with ReLU activation function
               output shape: hidden size defined in config
       Layer3: Fully connected layer with softmax activation function
               output shape: output size defined in config
       compile option: loss for data with categorical labels
                       stochastic gradient descent optimizer
                       accuracy metrics
       """
        ############################################## EDIT ################################################
        self.classifier.add(
            layers.Dense(self.config.hidden_size, activation='relu', input_shape=(self.config.input_size,)))
        self.classifier.add(layers.Dense(self.config.hidden_size, activation='relu'))
        self.classifier.add(layers.Dense(self.config.output_size, activation='softmax'))
        self.classifier.compile(optimizer='SGD', loss='categorical_crossentropy', metrics=['accuracy'])
        ####################################################################################################

        print("-------------------------MLP-------------------------\n", end='')
        self.train()
        self.inference()
        return self.test()
