import fft_mod.*

clear; close all;
ts = 1 / 4000;
fs = 1 / ts;
T1 = -0.05; T2 = 0.05;
time = T1:ts:T2;
df = 0.01;

B = 200 * 1.5; % 대역폭 1.5배
x = sinc(B*time).^2;

[X, x1, df_x] = fft_mod(x, ts, df);
X = X / fs;
X = fftshift(abs(X));
freq = (0:df_x:df_x*(length(x1)-1)) - fs/2;

AXIS_TIME = [-inf inf 0, 1.5];
AXIS_FREQ = [-5*B, 5*B, 0, 1.5*max(abs(X))];

sampling_freq = 2*B;

str_fs = [num2str(sampling_freq), 'Hz'];
sample_index = round(fs / sampling_freq);

x_s = zeros(1, length(x));
x_s(1:sample_index:end) = x(1:sample_index:end);

[X_s, x_s1, df_x_hat] = fft_mod(x_s, ts, df);
X_s = X_s / sampling_freq;
X_s = fftshift(abs(X_s));

% LPF (Reconstruction Filters)
analog_fps = 1500;
digital_fps = 5;
h = intfilt(analog_fps/digital_fps,4,0.9); 

x_up = upsample(x_s,analog_fps/digital_fps);
X_up = upsample(X_s,analog_fps/digital_fps);

x_r = filter(h,1,x_up);
x_r(1:floor(mean(grpdelay(h)))) = [];
x_r = [x_r zeros(1,floor(mean(grpdelay(h))))];

X_r = filter(h,1,X_up);
X_r(1:floor(mean(grpdelay(h)))) = [];
X_r = [X_r zeros(1,floor(mean(grpdelay(h))))];

x_d = downsample(x_r,analog_fps/digital_fps);
X_d = downsample(X_r,analog_fps/digital_fps);


figure
stem(time, x_d); hold on;
axis(AXIS_TIME); grid on;
xlabel('time [sec]'); 
title('f_{cutoff} / x_s = 5kHz / 40kHz')
disp('hit any key to see the spectrum'); pause  

figure
stem(freq, X_d); hold on;
axis(AXIS_FREQ); grid on;
xlabel('frequency [sec]'); 
title('f_{cutoff} / X_s = 5kHz / 40kHz')
disp('hit any key to see the time'); pause  