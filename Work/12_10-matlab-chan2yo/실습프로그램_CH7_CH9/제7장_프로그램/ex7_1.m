% ---------------------------------------------------------------
% ex7_1.m 
% Matlab program example for Sampling & Aliasing Effect
% CT signal is assumed to be sinc square pulse 
% ---------------------------------------------------------------
clear; close all;
ts = 1 / 2000;        % Sampling interval(time resolution) for Experiment
fs = 1 / ts;
T1 = -0.05; T2 = 0.05;
time = T1:ts:T2;       % Time vector
df = 0.01;             % Frequency resolution
% =========================================================================
B = 100;               % Signal bandwidth
x = sinc(B*time).^2;   % Original signal (sinc square)
% -------------------------------------------------------------------------
[X, x1, df_x] = fft_mod(x, ts, df);
X = X / fs;
X = fftshift(abs(X));
freq = (0:df_x:df_x*(length(x1)-1)) - fs/2;  % Frequency vector
% =========================================================================
AXIS_TIME = [-inf inf 0, 1.5];
figure
plot(time, x); axis(AXIS_TIME); grid on;
xlabel('time [sec]'); title('Original signal x(t)');
disp('hit any key to see the spectrum'); pause  
% -------------------------------------------------------------------------
AXIS_FREQ = [-5*B, 5*B, 0, 1.5*max(abs(X))];
figure
plot(freq, X); axis(AXIS_FREQ); grid on;
xlabel('frequency [Hz]'); title('Spectrum of original signal x(t)');
disp('hit any key to see the waveform of sampled signal'); pause  
% =========================================================================
sampling_freq = 2*B;           % Sampling frequency to see Aliasing Effect

str_fs = [num2str(sampling_freq), 'Hz'];
sample_index = round(fs / sampling_freq);
% Sampling
x_s = zeros(1, length(x));    % Sampled signal
x_s(1:sample_index:end) = x(1:sample_index:end);
% -------------------------------------------------------------------------
[X_s, x_s1, df_x_hat] = fft_mod(x_s, ts, df);
X_s = X_s / sampling_freq;
X_s = fftshift(abs(X_s));     % Spectrum of sampled signal
% -------------------------------------------------------------------------
figure
plot(time, x, 'k'); hold on;
stem(time, x_s); hold on;
axis(AXIS_TIME); grid on;
xlabel('time [sec]'); 
title(['Sampled signal, FS = ', str_fs]);
% -------------------------------------------------------------------------
disp('hit any key to see the spectrum of sampled signal'); pause  
figure
plot(freq, X_s);axis(AXIS_FREQ); grid on;
xlabel('frequency [Hz]'); 
title(['Spectrum of sampled signal, FS = ', str_fs]);
