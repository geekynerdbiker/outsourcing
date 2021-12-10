import fft_mod.*

clear; close all;
Ts = 1 / 4000;
Fs = 1 / Ts;
Time1 = -0.05; Time2 = 0.05;
Time = Time1:Ts:Time2;
Df = 0.01;

B = 200 * 2;  % 대역폭 2배
x = sinc(B*Time).^2;

[x2, x1, df_x] = fft_mod(x, Ts, Df);
x2 = x2 / Fs;
x2 = fftshift(abs(x2));
freq = (0:df_x:df_x*(length(x1)-1)) - Fs/2;

AXIS_TIME = [-inf inf 0, 1.5];
AXIS_FREQ = [-5*B, 5*B, 0, 1.5*max(abs(x2))];

sampling_freq = 2*B;

str_fs = [num2str(sampling_freq), 'Hz'];
sample_index = round(Fs / sampling_freq);

x_s = zeros(1, length(x));
x_s(1:sample_index:end) = x(1:sample_index:end);

[x2_s, x_s1, df_x_hat] = fft_mod(x_s, Ts, Df);
x2_s = x2_s / sampling_freq;
x2_s = fftshift(abs(x2_s));

figure
stem(Time, x_s); hold on;
axis(AXIS_TIME); grid on;
xlabel('time [sec]'); 
title(['Sampled signal, FS = ', str_fs]);
pause  

figure
stem(freq, x2_s); hold on;
axis(AXIS_FREQ); grid on;
xlabel('frequency [sec]'); 
title(['Sampled signal, FS = ', str_fs]);