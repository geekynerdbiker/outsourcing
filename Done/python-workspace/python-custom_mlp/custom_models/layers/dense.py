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
        input_dim = input_shape[-1]
        self.weights = np.random.randn(input_dim, self.units)
        self.bias = np.zeros(self.units)
        ####################################################################################################

    def call(self, x):
        self.input = x
        ############################################## EDIT ################################################
        z = np.dot(self.weights, x) + self.bias
        self.output = self.activation(z)
        ####################################################################################################
        return self.output

    def relu(self, x):
        ############################################## EDIT ################################################
        return np.maximum(0, x)
        ####################################################################################################
