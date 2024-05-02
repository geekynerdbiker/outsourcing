% Spectrum based on the first 10 samples of x(n)
N=10;
n=[0:N-1]; x = cos(0.48*pi*n)+cos(0.52*pi*n);
figure(1);
subplot(2,1,1); stem(n,x);
xlabel('n'); title('signal x(n), 0 <= n <= 9');
axis([0,N,-2.5,2.5])
X=fft(x);
magX=abs(X);
k=0:N-1; w=2*pi/10*k;
subplot(2,1,2); stem(w/pi,magX);
xlabel('frequency in pi units'); title('Magnitude of the 10-point DFT');
axis([0,2,0,10])

% High density spectrum (100 smaples) using zero-padding
N = 100;
n1=[0:N-1]; x1=[x(1:10) zeros(1,90)]; % 90 zeros are added
figure(2);
subplot(2,1,1); stem(n1,x1);
xlabel('n'); title('signal x(n), 0 <= n <= 9 + 90 zeros');
axis([0,N,-2.5,2.5])
X1=fft(x1);
magX1=abs(X1);
k1=0:N-1; w1=2*pi/100*k1;
subplot(2,1,2); plot(w1/pi, magX1); hold on; stem(w1/pi,magX1);
xlabel('frequency in pi units');
title('Magnitude of the 100-point DFT');
axis([0,2,0,10]);

% High resolution spectrum based on the 90 samples of the signal x(n)
N = 90;
n=[0:N-1]; x = cos(0.48*pi*n)+cos(0.52*pi*n);
figure(3);
subplot(2,1,1); stem(n,x);
title('signal x(n), 0 <= n <= 89'); xlabel('n');
axis([0,N,-2.5,2.5])
X=fft(x);
magX=abs(X);
k=0:N-1; w=2*pi/90*k;
subplot(2,1,2); stem(w/pi,magX);
xlabel('frequency in pi units'); title('Magnitude of the 90-point DFT');
axis([0,2,0,120])

% High resolution spectrum based on the 190 samples of the signal x(n)
N = 190;
n=[0:N-1]; x = cos(0.48*pi*n)+cos(0.52*pi*n);
figure(4);
subplot(2,1,1); stem(n,x);
title('signal x(n), 0 <= n <= 189'); xlabel('n');
axis([0,N,-2.5,2.5])
X=fft(x);
magX=abs(X);
k=0:N-1; w=2*pi/190*k;
subplot(2,1,2); stem(w/pi,magX);
xlabel('frequency in pi units');
title('Magnitude of the 90-point DFT');
axis([0,2,0,120])

% High resolution spectrum based on the 200 samples of the signal x(n)
N = 200;
n=[0:N-1]; x = cos(0.48*pi*n)+cos(0.52*pi*n);
figure(5);
subplot(2,1,1); stem(n,x);
title('signal x(n), 0 <= n <= 199'); xlabel('n');
axis([0,N,-2.5,2.5])
X=fft(x);
magX=abs(X);
k=0:N-1; w=2*pi/200*k;
subplot(2,1,2); stem(w/pi,magX);
xlabel('frequency in pi units');
title('Magnitude of the 200-point DFT');
