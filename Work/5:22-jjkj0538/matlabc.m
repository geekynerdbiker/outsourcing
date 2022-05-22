close all; clear; clc

Fs = 10000;

fi = fopen('output1.snd', 'rb');
x = fread(fi, inf, 'int16');
fclose(fi);
fi = fopen('output2.snd', 'rb');
x = fread(fi, inf, 'int16');
fclose(fi);

L = Fs*0.02; % a segment for short-time FFT (20 msec)

figure(1)
subplot(2,1,1); plot(x(1:L));
subplot(2,1,2); plot(y(1:L));

figure(2)
subplot(2,1,1); spectogram(x, hamming(256), 'yaxis');
subplot(2,1,2); spectogram(y, hamming(256), 'yaxis');