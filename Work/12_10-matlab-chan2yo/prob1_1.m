import fft_mod.*

clear; close all;
ts = 1 / 4000;
fs = 1 / ts;
T1 = -0.05; T2 = 0.05;
time = T1:ts:T2;
df = 0.01;

B = 200;
x = sinc(B*time).^2;

[X, x1, df_x] = fft_mod(x, ts, df);
X = X / fs;
X = fftshift(abs(X));
freq = (0:df_x:df_x*(length(x1)-1)) - fs/2;

AXIS_TIME = [-inf inf 0, 1.5];
figure
plot(time, x); axis(AXIS_TIME); grid on;
xlabel('time [sec]'); title('Original signal x(t)');
disp('hit any key to see the spectrum'); pause  

AXIS_FREQ = [-5*B, 5*B, 0, 1.5*max(abs(X))];
figure
plot(freq, X); axis(AXIS_FREQ); grid on;
xlabel('frequency [Hz]'); title('Spectrum of original signal x(t)');
disp('hit any key to see the time'); pause  