Fs = 8000;
fi = fopen('input.snd', 'rb');
x = fread(fi, inf, 'int16');
fclose(fi);
fi = fopen('output.snd', 'rb');
y = fread(fi, inf, 'int16');
fclose(fi);
figure(1)
subplot(2,1,1); plot(x);
title('Input signal')
subplot(2,1,2); plot(y);
title('Output signal')
print -djpeg 'fig1.jpg'
figure(2)
subplot(2,1,1); specgram(x);
title('Input signal')
subplot(2,1,2); specgram(y);
title('Output signal')
print -djpeg 'fig2.jpg'
soundsc(x,Fs);
pause
soundsc(y,Fs);