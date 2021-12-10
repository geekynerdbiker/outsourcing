import fft_mod.*

clear; close all;
ts = 1 / 4000;
fs = 1 / ts;
T1 = -0.05; T2 = 0.05;
time = T1:ts:T2;
df = 0.01;

B = 200 * 1.5;  % 대역폭 1.5배
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

figure
stem(time, x_s); hold on;
axis(AXIS_TIME); grid on;
xlabel('time [sec]'); 
title(['Sampled signal, FS = ', str_fs]);
disp('hit any key to see the spectrum'); pause  

figure
stem(freq, X_s); hold on;
axis(AXIS_FREQ); grid on;
xlabel('frequency [sec]'); 
title(['Sampled signal, FS = ', str_fs]);
disp('hit any key to see the time'); pause  