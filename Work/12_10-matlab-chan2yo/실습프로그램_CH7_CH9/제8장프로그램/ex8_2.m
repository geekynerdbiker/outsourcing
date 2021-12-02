close all; clear;
Rb = 1000;    fs = 40*Rb;
% -------------------------------------------------------------------------
% Effects of channel bandwidth(2500Hz, 800Hz, 500Hz)
% -------------------------------------------------------------------------
b = random_seq(20);
%b = [1 0 1 1 0 0 0 0 0 0 1 1 0 0 0 1 1 1 1 1];
[x, t] = linecode_gen(b, 'polar_nrz', Rb, fs);
y = channel_filter(x, 1, 0.0, 5000,fs);
subplot(211), waveform(x, fs); title('f_{cutoff} / f_s = 5kHz / 40kHz')
subplot(212), waveform(y, fs)
disp('hit any key to continue'); pause

y = channel_filter(x, 1, 0.0, 2500,fs);
subplot(211), waveform(x, fs); title('f_{cutoff} / f_s = 2.5kHz / 40kHz')
subplot(212), waveform(y, fs)
disp('hit any key to continue'); pause

y = channel_filter(x, 1, 0.0, 800,fs);
subplot(211), waveform(x, fs); title('f_{cutoff} / f_s = 0.8kHz / 40kHz')
subplot(212), waveform(y, fs)
disp('hit any key to continue'); pause

y = channel_filter(x, 1, 0.0, 500,fs);
subplot(211), waveform(x, fs); title('f_{cutoff} / f_s = 0.5kHz / 40kHz')
subplot(212), waveform(y, fs)

disp('hit any key to see the effects of noise'); pause
% -------------------------------------------------------------------------
% Effects of noise
% -------------------------------------------------------------------------
close all; 
noise_power = [0.01, 0.1, 0.5, 1.0];
f_cutoff = 5000;
y = channel_filter(x, 1, noise_power(1), f_cutoff,fs);
subplot(211), waveform(x, fs); title('noise power = 0.01')
subplot(212), waveform(y, fs)
disp('hit any key to continue'); pause

y = channel_filter(x, 1, noise_power(2), f_cutoff,fs);
subplot(211), waveform(x, fs); title('noise power = 0.1')
subplot(212), waveform(y, fs)
disp('hit any key to continue'); pause

y = channel_filter(x, 1,  noise_power(3), f_cutoff,fs);
subplot(211), waveform(x, fs); title('noise power = 0.5')
subplot(212), waveform(y, fs)
disp('hit any key to continue'); pause

y = channel_filter(x, 1,  noise_power(4), f_cutoff,fs);
subplot(211), waveform(x, fs); title('noise power = 1.0')
subplot(212), waveform(y, fs)

disp('hit any key to see PSD'); pause
% -------------------------------------------------------------------------
% PSD of channel filter output
% -------------------------------------------------------------------------
b = random_seq(2000);
x = linecode_gen(b, 'polar_nrz', Rb, fs);
figure; subplot(121), psd_est(x,fs, 'decibel'); a = axis;
title('PSD of line code waveform');
y=channel_filter(x, 1, 0.01, 5000, fs);
subplot(122), psd_est(x,fs, 'decibel'); axis(a), hold on
pause; disp('Press any key to continue');
psd_est(channel_filter(x, 1, 0.1, 5000, fs), fs, 'decibel');
pause; disp('Press any key to continue');
psd_est(channel_filter(x, 1, 0.5, 5000, fs), fs, 'decibel');
pause; disp('Press any key to continue');
psd_est(channel_filter(x, 1, 1, 5000, fs), fs, 'decibel');
title('PSD of channel filter output');
legend('noise pwr 0.01', 'noise pwr 0.1','noise pwr 0.5','noise pwr 1.0')