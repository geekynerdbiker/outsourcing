close all; clear all; clc

% Load MNIST dataset.
load('training_data.mat')
fprintf('Training\nnumimages = %d, size of images : %d X %d\n',...
    size(inputValues,2),sqrt(size(inputValues,1)),sqrt(size(inputValues,1)))

size(inputValues)
% Transform the labels to correct target values.
targetValues = 0.*ones(10, size(labels, 1));

size(targetValues)
for n = 1: size(labels, 1)
    targetValues(labels(n) + 1, n) = 1;
end
    
% Choose form of MLP:
numberOfHiddenUnits = 100;

% Choose appropriate parameters.
learningRate = 0.1;
    
% Choose activation function.
activationFunction = @logisticSigmoid;
dActivationFunction = @dLogisticSigmoid;
    
% Choose batch size and epochs.
batchSize = 100;
epochs = 500;
    
fprintf('Train two layer perceptron with %d hidden units.\n', numberOfHiddenUnits);
fprintf('Learning rate: %d.\n', learningRate);
    
[hiddenWeights, outputWeights, error] = ...
    trainStochasticSquaredErrorTwoLayerPerceptron(...
    activationFunction, dActivationFunction, numberOfHiddenUnits, inputValues, ...
    targetValues, epochs, batchSize, learningRate);
    
% Load validation set.
load('test_data.mat')

fprintf('Test\nnumimages = %d, size of images : %d X %d\n', ...
    size(inputValues,2),sqrt(size(inputValues,1)),sqrt(size(inputValues,1)))

size(inputValues)

% Choose decision rule.
fprintf('Validation:\n');
    
[correctlyClassified, classificationErrors] = ...
    validateTwoLayerPerceptron(activationFunction, hiddenWeights, ...
    outputWeights, inputValues, labels);
    
fprintf('Classification errors: %d\n', classificationErrors);
fprintf('Correctly classified: %d\n', correctlyClassified);
recognition_rate = 100*correctlyClassified/size(inputValues,2);
fprintf('Recognition rate: %.2f\n', recognition_rate);

% save and show some images
figure
for i=0:9
    I = reshape(inputValues(:, i*100+1), 28, 28);
    if i == 0
        size(I)
    end    
    imwrite(reshape(inputValues(:,i*100+1), 28, 28), strcat(num2str(i*100+1), '.png'));
    img=imread(strcat(num2str(i*100+1), '.png'));
    subplot(2,5,i+1);
    imshow(img);
end