%% 가우시안 필터에서 weight값은 가까운 정도에 따라 결정된다. 중심의 웨이트가 제일 크고 센터에서 멀어질수록 값이 작아진다. 가우시안 필터는 시그마에 따라 스무딩되는 영역이 달라진다. 시그마가 작으면 좁은 부위에서 감소가 빠르게 일어나고, 크면 넓은 부위에서 감소가 느리게 일어난다. 또한 시그마 값과 최댓값은 반비례 관계에 있다.
close all; clear all; clc;

im = imread('Lenna_salt_pepper.png');
im = im2double(im);
sigma = 3;

result = gaussianFiltering(im, sigma);

imwrite(result, 'result_GaussianFilter_3.png'); 

%% 연달아 발생한 노이즈를 제거하기 위해서 filterSize를 크게 할 수 있지만, 필터사이즈가 클수록 더 많은 영역에서 중간값을 사용하므로 이미지의 윤곽이 더 많이 무너진다는 것을 확인할 수 있다.
close all; clear all; clc;

im = imread('Lenna_salt_pepper.png');
filterSize = [7,7];

result = medianFiltering(im, filterSize);

imwrite(result, 'result_medianFilter_7x7.png'); 
