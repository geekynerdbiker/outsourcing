import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

class NeuralNetwork {

    private int inputSize;
    private int hiddenSize;
    private int outputSize;

    private double[][] weights1;
    private double[][] weights2;

    public NeuralNetwork(int inputSize, int hiddenSize, int outputSize) {
        this.inputSize = inputSize;
        this.hiddenSize = hiddenSize;
        this.outputSize = outputSize;

        this.weights1 = new double[inputSize][hiddenSize];
        for (int i = 0; i < inputSize; i++) {
            for (int j = 0; j < hiddenSize; j++) {
                weights1[i][j] = Math.random();
            }
        }

        this.weights2 = new double[hiddenSize][outputSize];
        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                weights2[i][j] = Math.random();
            }
        }
    }

    public void update(int state, int actualMoves, int loss) {
        // Calculate the error
        double[] error = new double[outputSize];
        for (int i = 0; i < outputSize; i++) {
            error[i] = actualMoves - weights2[i][0];
        }

        // Backpropagate the error
        double[] hiddenError = new double[hiddenSize];
        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                hiddenError[i] += weights2[i][j] * error[j];
            }
        }

        // Update the weights
        for (int i = 0; i < inputSize; i++) {
            for (int j = 0; j < hiddenSize; j++) {
                weights1[i][j] += error[0] * hiddenError[j] * learningRate;
            }
        }

        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                weights2[i][j] += hiddenError[i] * error[j] * learningRate;
            }
        }
    }

    public int predict(int state) {
        double[] input = new double[inputSize];
        for (int i = 0; i < inputSize; i++) {
            input[i] = (state >> i) & 1;
        }

        double[] hidden = new double[hiddenSize];
        for (int i = 0; i < hiddenSize; i++) {
            for (int j = 0; j < inputSize; j++) {
                hidden[i] += input[j] * weights1[j][i];
            }
        }

        double[] output = new double[outputSize];
        for (int i = 0; i < outputSize; i++) {
            for (int j = 0; j < hiddenSize; j++) {
                output[i] += hidden[j] * weights2[j][i];
            }
        }

        int max = Integer.MIN_VALUE;
        for (int i = 0; i < outputSize; i++) {
            if (max < output[i])
                max = (int)output[i];
        }

        return max;
    }

    private double learningRate = 0.01;

    public void load(ObjectInputStream in) throws IOException, ClassNotFoundException {
        learningRate = in.readDouble();
        weights1 = (double[][]) in.readObject();
        weights2 = (double[][]) in.readObject();
    }

    public void save(ObjectOutputStream out) throws IOException {
        out.writeDouble(learningRate);
        out.writeObject(weights1);
        out.writeObject(weights2);
    }
}