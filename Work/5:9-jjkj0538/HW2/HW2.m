close all; clear all; clc;

im = imread('Lenna_salt_pepper.png');
im = im2double(im);
sigma = 5;

result = gaussianFiltering(im, sigma);

imwrite(result, 'result_GaussianFilter.png'); 

%%
close all; clear all; clc;

im = imread('Lenna_salt_pepper.png');
filterSize = [3,3];

result = medianFiltering(im, filterSize);

imwrite(result, 'result_medianFilter.png'); 
