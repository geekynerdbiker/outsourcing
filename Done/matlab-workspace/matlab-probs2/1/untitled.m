clear; close all; clc

[input_x, Fs] = audioread('8k16bit.wav');
bp=10000;
x=input_x(bp:bp+239);
size(x)
x=x';
size(x)
N=length(x);
Ts=1/Fs;
t=0:Ts:(N-1)*Ts;
y=x+cos(2*pi*1000*t)/10;

x_energy=sum(x.^2); % 각 원소 제곱 합
sss = sprintf('signal energy = %f', x_energy);
disp(sss);

x_power=sum(x.^2/240);  % (각 원소 제곱 / 크기)의 합
sss = sprintf('signal power = %f', x_power);
disp(sss);

subplot(3,1,1); plot(input_x);
axis([1 length(input_x) -0.3 0.3]);
n=bp:bp+239;
subplot(3,1,2); plot(n,x);
axis([bp bp+239 -0.3 0.3]);
subplot(3,1,3); plot(n,y);
axis([bp bp+239 -0.3 0.3]);
print -djpeg 'fig1.jpg'

mu_x=sum(x)/numel(x);   % x 평균
mu_y=sum(y)/numel(y);   % y 평균
sigma_x=sqrt(sum((x-mu_x).^2)/numel(x));    % x 표준편차
sigma_y=sqrt(sum((y-mu_x).^2)/numel(y));    % y 표준편차
cov_xx=sum((x-mu_x).*(x-mu_x))/numel(x);    % x 공분산
cov_xy=sum((x-mu_x).*(y-mu_y))/numel(y);    % y 공분산

corr_xx=cov_xx/(sigma_x*sigma_x);   % x 상관계수
corr_xy=cov_xy/(sigma_x*sigma_y);   % y 상관계수

sss=sprintf('normalized correlation coefficient = %f', corr_xx);
disp(sss);
sss=sprintf('normalized correlation coefficient = %f', corr_xy);
disp(sss);

sss=sprintf('%f',corrcoef(x,y));
disp(sss);

N=100;
x=-0.5+(0.5+0.5).*rand(N, 1);   % x: uniform distribution (-0.5 ~ 0.5)
y=-0.5+(0.5+0.5).*rand(N, 1);   % y: uniform distribution (-0.5 ~ 0.5)
figure(2);
subplot(2,2,1); stem(x); title('x = -0.5 ~ 0.5');
subplot(2,2,2); stem(y); title('y = -0.5 ~ 0.5');
corrcoef(x,y);

x=randn(1,numel(x));   % x: normal distribution
y=randn(1,numel(y));   % y: normal distribution
subplot(2,2,3); stem(x); title('x: normal distribution');
subplot(2,2,4); stem(y); title('y: normal distribution');
sss=sprintf('%f',corrcoef(x,y));
disp(sss);


n=0:N-1;
freq=100;
Fs=10000;
Ts=1/Fs;
x=cos(2*pi*freq*n*Ts); y=cos(2*pi*freq*n*Ts-pi/2);
figure(3);
subplot(2,1,1); stem(n,x);
subplot(2,1,2); stem(n,y);
corrcoef(x,y);