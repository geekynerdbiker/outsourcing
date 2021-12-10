import fft_mod.*

clear; close all;
Ts = 1 / 4000;
Fs = 1 / Ts;
Time1 = -0.05; Time2 = 0.05;
Time = Time1:Ts:Time2;
Df = 0.01;

B = 200;
x = sinc(B*Time).^2;

[x2, x1, df_x] = fft_mod(x, Ts, Df);
x2 = x2 / Fs;
x2 = fftshift(abs(x2));
freq = (0:df_x:df_x*(length(x1)-1)) - Fs/2;

AXIS_TIME = [-inf inf 0, 1.5];
figure
plot(Time, x); axis(AXIS_TIME); grid on;
xlabel('time [sec]');
title('Original signal x(t)');
pause

AXIS_FREQ = [-5*B, 5*B, 0, 1.5*max(abs(x2))];
figure
plot(freq, x2); axis(AXIS_FREQ); grid on;
xlabel('frequency [Hz]'); 
title('Spectrum of original signal x(t)');
pause