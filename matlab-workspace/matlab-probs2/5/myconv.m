% Linear convolution vs.
% Fast convolution using FFT
clear; close all; clc

% read the input signal
filename='8k16bit.wav';
[x,Fs] = audioread(filename);
% read the impulse response
filename='RIR1.wav';
[rir, Fs_rir] = audioread(filename);

figure(1)
subplot(2,1,1); plot(x); title('input signal')
subplot(2,1,2); plot(rir); title('room impulse response');
print -djpeg 'fig1.jpeg'

% Linear convolution
disp('<Linear convolution>')
tic % to calculate "Elapsed time"
y = conv(x, rir);
disp('<Fast convolution using FFT>')

% Fast convolution using FFT
tic
y_fast = myfastconv(x, rir);
toc

figure(2)
subplot(2,1,1); plot(y); 
title('output signal by linear convolution');
subplot(2,1,2); plot(y_fast); 
title('output signal by fast convolution')
print -djpeg 'fig2.jpeg'

figure(3)
specgram(x)
print -djpeg 'fig3.jpeg'
figure(4)
specgram(y)
print -djpeg 'fig4.jpeg'

Lx = length(x);
Lrir = length(rir);
Ly = length(y);
sss = sprintf('\nLy = %d', Ly);
disp(sss);
sss = sprintf('Ly = %d + %d - 1 = %d\n', Lx, Lrir, Ly);
disp(sss);

corr_value = corr(y, y_fast);
sss = sprintf('Correlation between y and y_fast = %f', corr_value);
disp(sss);

soundsc(x, Fs);
audiowrite('input.wav', x, Fs); pause
soundsc(rir, Fs);
audiowrite('rir.wav', rir, Fs); pause
soundsc(y, Fs);
audiowrite('output.wav', y, Fs); pause
soundsc(y_fast, Fs);
audiowrite('output_fast.wav', y_fast, Fs); pause