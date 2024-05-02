% 1.1
n = [0:31];
x = sin(2*pi*220*n/2048);

x_padded = [x zeros(1,1024-32)];
X_padded = fft(x_padded);
X = fft(x);

figure;
plot(2048/1024*(0:1023), abs(X_padded)); hold on;
stem((0:31)*64, abs(X));
xlabel('Frequency (Hz)');
ylabel('|X|');
ylim([0 16])
xlim([0 1024])
xticks([0:9]*110)

% % 1.2
n = [0:31];
x = sin(2*pi*128*n/2048);

x_padded = [x zeros(1,1024-32)];
X_padded = fft(x_padded);
X = fft(x);

figure;
plot(2048/1024*(0:1023), abs(X_padded));
xlabel('Frequency (Hz)');
ylabel('|X|');
ylim([0 16])
xlim([0 1024])
xticklabels([0:9]*110)

%1.3
n = [0:31];
x = sin(2*pi*128*n/2048)+0.2*sin(2*pi*220*n/2048)+0.01*cos(2*pi*525*n/2048);

x_padded = [x zeros(1,1024-32)];
X_padded = fft(x_padded);
X = fft(x);

% figure;
plot(2048/1024*(0:1023), abs(X_padded));
xlabel('Frequency (Hz)');
ylabel('|X|');
ylim([0 20])
xlim([0 1024])
xticklabels([0:9]*110)

%2.1
w1=arrayfun(@(n) 1, (0:31));
w2=arrayfun(@(n) (15-abs(n-15))*2/30, (0:30));
w3=arrayfun(@(n) sin(pi*n/31), (0:31));
w4=arrayfun(@(n) 0.5*(1-cos(2*pi*n/31)), (0:31));

subplot(2,2,1)
plot((0:31), w1)
gtext("Rectangular");

subplot(2,2,2)
plot((0:30), w2)
gtext("Triangular");

subplot(2,2,3)
plot((0:31), w3)
gtext("Sine");

subplot(2,2,4)
plot((0:31), w4)
gtext("Hann");

% %2.2
W1=abs(fft(w1, 1024));
W2=abs(fft(w2, 1024));
W3=abs(fft(w3, 1024));
W4=abs(fft(w4, 1024));

figure
subplot(2,2,1);
plot(fftshift(W1));
title('Rectangular')
xticks([0 512 1024])
xticklabels([-0.5 0 0.5])
ylim([0 32])

subplot(2,2,2);
plot(fftshift(W2));
title('Triangular')
xticks([0 512 1024])
xticklabels([-0.5 0 0.5])

subplot(2,2,3);
plot(fftshift(W3));
title('Sine')
xticks([0 512 1024])
xticklabels([-0.5 0 0.5])

subplot(2,2,4);
plot(fftshift(W4));
title('Hann')
xticks([0 512 1024])
xticklabels([-0.5 0 0.5])


%2-3
figure
rect = 20 * log10(abs(fftshift(W1)));
tri = 20 * log10(abs(fftshift(W2)));

plot(linspace(0, 1, length(W1)), rect); hold on;
plot(linspace(0, 1, length(W2)), tri, '--');
legend(["Rectangular", "Triangular"])

xlim([0.3 0.7])
xticks([0.3:0.05:0.7])
xticklabels((0.3:0.05:0.7)-0.5)
xlabel('Normalized Frequency');

ylim([-80 0]+32)
yticks([-80:10:0]+32)
yticklabels([-80:10:0])
ylabel('Magnitude (dB)');

%2-6
figure
sine = 20 * log10(abs(fftshift(W3)));
hann = 20 * log10(abs(fftshift(W4)));

plot(linspace(0, 1, length(W3)), sine); hold on;
plot(linspace(0, 1, length(W4)), hann, '--');
legend(["Sine", "Hann"])

xlim([0.3 0.7])
xticks([0.3:0.05:0.7])
xticklabels((0.3:0.05:0.7)-0.5)
xlabel('Normalized Frequency');

ylim([-80 0]+32)
yticks([-80:10:0]+32)
yticklabels([-80:10:0])
ylabel('Magnitude (dB)');

%3-1
figure
subplot(2,2,1)
stem((0:31), abs(fft(x.*w1))./max(abs(fft(x.*w1))))
title('Rectangular')
xlim([0 15])
xticks([0 2 3 8 15])
xticklabels([0 128 220 525 1024])

subplot(2,2,2)
stem((0:31), abs(fft(x.*[w2 0]))./max(abs(fft(x.*[w2 0]))))
title('Triangular')
xlim([0 15])
xticks([0 2 3 8 15])
xticklabels([0 128 220 525 1024])

subplot(2,2,3)
stem((0:31), abs(fft(x.*w3))./max(abs(fft(x.*w3))))
title('Sine')
xlim([0 15])
xticks([0 2 3 8 15])
xticklabels([0 128 220 525 1024])
xlabel('Frequency (Hz)')

subplot(2,2,4);
stem((0:31), abs(fft(x.*w4))./max(abs(fft(x.*w4))))
title('Hann')
xlim([0 15])
xticks([0 2 3 8 15])
xticklabels([0 128 220 525 1024])
xlabel('Frequency (Hz)')

%3-2
figure
subplot(2,2,1)
plot((0:2047), abs(fft(x.*w1, 2048))./max(abs(fft(x.*w1, 2048))))
title('Rectangular')
xlim([0 1023])

subplot(2,2,2)
plot((0:2047), abs(fft(x.*[w2 0], 2048))./max(abs(fft(x.*[w2 0], 2048))))
title('Triangular')
xlim([0 1023])

subplot(2,2,3)
plot((0:2047), abs(fft(x.*w3, 2048))./max(abs(fft(x.*w3, 2048))))
title('Sine')
xlim([0 1023])

subplot(2,2,4);
plot((0:2047), abs(fft(x.*w4, 2048))./max(abs(fft(x.*w4, 2048))))
xlim([0 1023])