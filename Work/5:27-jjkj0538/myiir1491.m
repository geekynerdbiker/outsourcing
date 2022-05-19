close all; clear; clc

% Make signal ------------------------------
dur = 1; % [sec]
fm = 300; % frequency of message signal
fn = 3000; % frequency of noise signal
Fs = 10000; %sampling frequency
N = Fs * dur; % total number of samples
Ts= 1/Fs; %sampling period

n = 0:N-1;
xm = 0.5*sin(n*Ts*2*pi*fm); % message signal
xn = 0.5*sin(n*Ts*2*pi*fn); % noise signal
x = xm + xn; % -1.0 ~ 1.0
x = x * 32767; % -32767 ~ 32767

% Filter design ------------------------------
M = 8; % filter order
fc = 2000; % cutoff frequency (Hz). 0 < fc < Fs/2
% normalized cutoff frequency (rad). 0 < wc < 1
wc = fc/(Fs/2);

[B, A] = cheby1(M, 0.5, wc, 'low'); % filter design

% write the filter coefficients to a file
fid = fopen('coeffs_fir.txt','w');
fprintf(fid,'%e\n',B);
fprintf(fid,'%e\n',A);
fclose(fid);

L = Fs*0.02; % a segment for short-time FFT (20 msec)

[H, w] = freqz(B,A,L); %frequency response
% magnitude response
magH = abs(H);
dBH = 20*log10(magH./max(magH)); % in dB

y=filter(B,1,x); % filtering

Xk = fftshift(fft(x(1:L))); % first L samples
Yk = fftshift(fft(y(1:L))); % first L samples
delta_f = Fs/L;
freq_axis = delta_f*(-L/2:L/2-1); % -Fs/2 ~ (Fs/2 - delta_f)

% Plotting ------------------------------
figure(1)
subplot(3,1,1); stem(0:M,B); grid;
title('Filter coefficients');
subplot(3,1,2); plot(w/pi,magH); grid;
title('Magnitude response');
subplot(3,1,3); plot(w/pi,dBH); grid;
title('Magnitude response in dB');
print -djpeg 'IIR_fig1.jpg'

figure(2)
subplot(2,2,1); plot(0:L-1,x(1:L));
title('Signal amplitude before filtering');
subplot(2,2,2); plot(freq_axis,abs(Xk));
title('Freq. components before filtering');
subplot(2,2,3); plot(0:L-1,y(1:L));
title('Signal amplitude after filtering');
subplot(2,2,4); plot(freq_axis,abs(Yk));
title('Freq. components after filtering');
print -djpeg 'IIR_fig2.jpg'

figure(3)
subplot(2,1,1); spectrogram(x, hamming(256), 'MinThreshold', 15, 'yaxis');
title('Spectruogram before filtering');
subplot(2,1,2); spectrogram(y, hamming(256), 'MinThreshold', 15, 'yaxis');
title('Spectruogram after filtering');
print -djpeg 'IIR_fig3.jpg'

fid = fopen('input.snd','wb');
fwrite(fid,x,'int16'); % write the input signal to a file
fclose(fid);
fid = fopen('outut_FIR.snd','wb');
fwrite(fid,y,'int16'); % write the output signal to a file
fclose(fid);

soundsc(x,Fs0); % before filtering
puase(2*N/Fs) % 2 * dur
soundsc(y,Fs); % after filtering