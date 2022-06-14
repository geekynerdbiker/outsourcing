close all; clear; clc;

Fs = 8000;

fi = fopen('input.snd', 'rb');
x = fread(fi, inf, 'int16');
fclose(fi);
fi = fopen('outputLPF.snd', 'rb');
yLPF = fread(fi, inf, 'int16');
fclose(fi);
fi = fopen('outputHPF.snd', 'rb');
yHPF = fread(fi, inf, 'int16');
fclose(fi);

figure(1)
subplot(3,1,1); plot(x); title('Input signal');
subplot(3,1,2); plot(yLPF); title('Output signal (LPF)');
subplot(3,1,3); plot(yHPF); title('Output signal (HPF)');
print -djpeg 'fig1.jpg'

figure(2)
subplot(3,1,1); specgram(x); title('Input specgram');
subplot(3,1,2); specgram(yLPF); title('Output specgram (LPF)');
subplot(3,1,3); specgram(yHPF); title('Output specgram (HPF)');
print -djpeg 'fig2.jpg'

soundsc(x,Fs)
pause
soundsc(yLPF,Fs)
pause
soundsc(yHPF,Fs)
