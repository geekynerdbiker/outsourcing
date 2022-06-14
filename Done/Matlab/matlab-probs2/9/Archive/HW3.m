
close all; clear all; clc;

im = imread('Lenna_salt_pepper.png');
im = im2double(im);

result = SobelEdge(im);
imwrite(result, 'result_SobelEdge.png'); 

im = medfilt2(im);
result = SobelEdge(im);
imwrite(result, 'result_SobelEdge_medianFilter.png'); 

%%

close all; clear all; clc;

im1 = imread('Notre_Dame_1.png');
im2 = imread('Notre_Dame_2.png');

% Harris Corner Detector

fx_operator = [-1,0,1]; % vector for derivative
fy_operator = [-1;0;1]; % vector for derivative
Gaussian_sigma = 3; % standard deviation for Gaussian filtering
k = 0.04; % k for C
C_thres = 0.05; % relative threshold for C
NMS_ws = 7; % window size for non-maximum suppression

[corner1, C1] = detectHarrisCorner(im1, fx_operator, fy_operator, ...
    Gaussian_sigma, k, C_thres, NMS_ws);
[corner2, C2] = detectHarrisCorner(im2, fx_operator, fy_operator, ...
    Gaussian_sigma, k, C_thres, NMS_ws);

C1 = C1/max(C1(:));
C2 = C2/max(C2(:));

imwrite(C1, 'Cornerness_1.jpg');
imwrite(C2, 'Cornerness_2.jpg');

corner1 = [corner1, 3*ones(size(corner1,1),1)];
corner2 = [corner2, 3*ones(size(corner2,1),1)];

im1_corner = insertShape(im1, 'Circle',  corner1, 'LineWidth', 2, 'Color', 'green');
im2_corner = insertShape(im2, 'Circle',  corner2, 'LineWidth', 2, 'Color', 'green');

imwrite(im1_corner, 'CornerDetection_1.jpg');
imwrite(im2_corner, 'CornerDetection_2.jpg');

