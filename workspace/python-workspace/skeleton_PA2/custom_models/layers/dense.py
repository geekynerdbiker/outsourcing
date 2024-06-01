# -*- coding: utf-8 -*-

#   *** Do not import any library except already imported libraries ***
import numpy as np
from . import Layer
#   *** Do not import any library except already imported libraries ***


class Dense(Layer):
    def __init__(self, units: int, activation: str, input_shape: tuple = None):
        """
        Dense implements the operation: output = activation(dot(weights, input) + bias) 
        where activation is the element-wise activation function passed as the activation argument, 
        weights is a matrix created by the layer, and bias is a bias vector created by the layer 
        """
        super(Dense, self).__init__(units, activation, input_shape)
        self.units = units
        self.activation = self.activation_fn(fn_name=activation)

    def build(self, input_shape):
        ############################################## EDIT ################################################
        limit = np.sqrt(6 / (input_shape[0] + self.units))
        self.weights = np.random.uniform(low=-limit, high=limit, size=(self.units, input_shape[0]))
        self.bias = np.zeros((self.units, 1))
        self.bias = np.zeros((self.units, 1))
        ####################################################################################################

    def call(self, x):
        self.input = x
        ############################################## EDIT ################################################
        if not self.built:
            self.build(x.shape)
            self.built = True
        z = np.dot(self.weights, x) + self.bias

        self.output = self.activation(z)
        ####################################################################################################
        return self.output

    def relu(self, x):
        ############################################## EDIT ################################################
        return np.maximum(0, x)
        ####################################################################################################
