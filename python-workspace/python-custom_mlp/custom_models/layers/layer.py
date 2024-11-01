import numpy as np

class Layer:
    def __init__(self, units: int, activation: str, input_shape: tuple = None, use_bias: bool = True):
        self.units = units
        self.use_bias = use_bias
        if input_shape is not None:
            self.build(input_shape)
            self.built = True
        else:
            self.built = False

        self.activation = self.activation_fn(fn_name=activation)

    def __call__(self, x):
        if not self.built:
            self.build(x.shape)
            self.built = True
        return self.call(x)
    
    def build(self, input_shape):
        raise NotImplementedError

    def call(self, x):
        raise NotImplementedError

    def activation_fn(self, fn_name='relu'):
        if fn_name == 'relu':
            return self.relu
        elif fn_name == 'softmax':
            return self.softmax

    def relu(self, x):
        raise NotImplementedError

    def softmax(self, x):
        if np.sum(np.exp(x)) == 0:
            import pdb; pdb.set_trace()
        return np.exp(x) / np.sum(np.exp(x))

