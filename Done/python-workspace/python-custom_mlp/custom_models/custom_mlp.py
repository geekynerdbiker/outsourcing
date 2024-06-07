# -*- coding: utf-8 -*-

#   *** Do not import any library except already imported libraries ***
from . import layers
from utils import calculate_score
from tqdm import tqdm, trange
import sys
import random
import numpy as np
import pandas as pd

sys.path.append("..")


#   *** Do not import any library except already imported libraries ***


class CustomMLP:
    def __init__(self, config, dataset):
        self.config = config
        ############################################## EDIT ################################################
        self.X_train = dataset.sequences_to_matrix(dataset.X_train, mode='binary')
        self.X_test = dataset.sequences_to_matrix(dataset.X_test, mode='binary')
        self.X_inference = dataset.sequences_to_matrix(dataset.X_inference, mode='binary')
        self.y_train = dataset.to_categorical(dataset.y_train)
        self.y_test = dataset.to_categorical(dataset.y_test)

        self.output = None
        self.label = None
        self.error = None
        ####################################################################################################

        self.lr = config.learning_rate
        self.layers = list()

    def add(self, layer: layers.Dense):
        self.layers.append(layer)

    def forward(self, x):
        """
        Calculate the model's predicted value for the input by calculating the forward propagation of the model.

        Process:
        1. Reshape input to (input_size, 1).
        2. Calculate the hidden value using the layer added to self.layers.
        3. The hidden value of the last layer is used as output.

        Outputs:
        Predicted value of model.
        """
        ############################################## EDIT ################################################
        x = x.reshape(-1, 1)
        
        for layer in self.layers:
            x = layer.call(x)

        return x
        ####################################################################################################

    def backward(self):
        """
        Calculate the weight gradient and bias gradient of each layer using the gradient descent algorithm.

        Hint: start calculation from the last layer using the chain rule.
        """
        ############################################## EDIT ################################################
        dW = np.zeros_like(self.layers[-1].weights)
        db = np.zeros_like(self.layers[-1].bias)

        self.error = self.output - self.label
        dW = np.dot(self.layers[-1].input.T, self.error)
        db = np.sum(self.error, axis=0)

        for i in range(len(self.layers) - 2, -1, -1):
            self.error = np.dot(self.error, self.layers[i + 1].weights.T) * self.layers[i].activation_derivative(self.layers[i].input)
            dW = np.dot(self.layers[i].input.T, self.error)
            db = np.sum(self.error, axis=0)

            self.layers[i].weights -= self.lr * dW
            self.layers[i].bias -= self.lr * db
        ####################################################################################################

    def step(self):
        for layer in self.layers:
            layer.weights -= self.lr * layer.grad_w
            layer.bias -= self.lr * layer.grad_b

    def loss(self, label, logits):
        self.label = label.reshape(logits.shape)
        return -np.sum(self.label * np.log(logits))  # Cross Entropy Loss

    def fit(self, x, y, epochs, validation_data):
        d = list(zip(x, y))
        for epoch in trange(epochs, desc='Epoch Iterator'):
            epoch_loss = 0.

            random.shuffle(d)
            for train_vec, label in tqdm(d, desc='Train Iterator'):
                ############################################## EDIT ################################################
                """
                After forward propagation and loss calculation, back propagation and weight adjustment are performed.
                The calculated loss is added to epoch_loss.
                """

                self.output = self.forward(train_vec)
                self.error = self.loss(label, self.output)
                self.backward()
                self.step()

                epoch_loss += self.error
                ####################################################################################################
            print('Epoch : {} | Train Loss : {:.4f}'.format(
                epoch + 1, epoch_loss / len(d)))
            self.evaluate(*validation_data)

    def evaluate(self, x, y):
        d = list(zip(x, y))
        eval_loss = 0.
        preds = list()
        for test_vec, label in tqdm(d, desc='Eval Iterator'):
            ############################################## EDIT ################################################
            """
            Save the model’s predicted value through forward calculation and calculate loss.
            Weight adjustment is not performed during evaluation.
            """

            self.output = self.forward(test_vec)
            self.error = self.loss(label, self.output)

            eval_loss += self.error
            preds.append(np.argmax(self.output))
            ####################################################################################################

        preds = np.array(preds)
        result = calculate_score(y, preds)
        print('Eval Loss : {:.4f} | Eval Score : {:.2f}'.format(
            eval_loss / len(d), result['accuracy'][0]))

        return result

    def inference(self):

        preds = list()
        for test_vec in self.X_inference:
            ############################################## EDIT ################################################
            """
            Save the model’s predicted value through forward calculation
            Weight adjustment and calculate loss is not performed during inference.
            """

            test_vec = test_vec.reshape(-1, 1)
            logit = self.forward(test_vec)
            preds.append(np.argmax(logit))
            ####################################################################################################
        preds = np.array(preds)

        test_df = pd.read_csv('data/test.csv')
        test_df['Emotion'] = preds
        output_df = test_df[['id', 'Emotion']]
        output_df.to_csv(f'output/custom_mlp_predictions.csv', index=False)

    def run(self):
        print("-------------------------Custom MLP-------------------------\n", end='')
        self.add(layers.Dense(units=self.config.hidden_size,
                              activation='relu', input_shape=(self.config.input_size,)))
        self.add(layers.Dense(units=self.config.hidden_size, activation='relu'))
        self.add(layers.Dense(units=self.config.output_size, activation='softmax'))
        self.fit(self.X_train,
                 self.y_train,
                 epochs=self.config.epochs,
                 validation_data=(self.X_test, self.y_test)
                 )
        self.inference()
        return self.evaluate(self.X_test, self.y_test)
