clear; close all; clc;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DFT of real data
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[input_x, Fs] = audioread('8k16bit.wav');
bp =10000;
N = 240;
x=input_x(bp:bp+N-1); %일부 구간: 240 samples (30msec)
gain = 2;
x = x * gain;
x = x';
n=0:N-1;
figure(1)
subplot(2,1,1);stem(n,x);
title('signal x(n)');xlabel('n');
axis([0, N, -0.5, 0.5]);
X=fft(x);
magX=abs(X);
k=0:N-1;
w=2*pi/N*k; % [0, 2*pi) 구간을 N개로 샘플링
subplot(2,1,2);stem(w/pi,magX);
xlabel('frequency in pi units');title('Magnitude spectrum |X(k)|');
axis([0,2,0,30]);

Ts = 1/Fs;
t = 0:Ts:(N-1)*Ts;
freq_tone = 1000;
y = x + cos(2*pi*freq_tone*t)/5; % tone signal is added
figure(2);
subplot(2,1,1);stem(n,y);
title('signal y(n)');xlabel('n');
axis([0, N, -0.5, 0.5]);
Y=fft(y);
magY=abs(Y);
k=0:N-1;
w=2*pi/N*k; % 0 ~ 2*pi 구간을 N개로 샘플링
subplot(2,1,2);stem(w/pi, magY);
xlabel('frequency in pi units');title('Magnitude spectrum |Y(k)|');
axis([0,2,0,30]);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DTFT ans 4-point DFT (smapling in frequency domain)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
h = [1,2,2,1];

% DTFT
M = 500; k = 0:M-1; % M points
w = [0:1:M]*2*pi/M; % digital radian frequencies, [0, 2*pi)
H = freqz(h,1,w); % frequency response
magH = abs(H); phaH = angle(H)*180/pi; % phase in degree
figure(3);
subplot(2,1,1);plot(w/pi, magH); grid;
xlabel('frequency in pi units'); ylabel('|H|');
title('Magnitude spectrum |Y(k)|');
subplot(2,1,2);plot(w/pi, phaH); grid;
xlabel('frequency in pi units'); ylabel('Degree');
title('Angle of the DTFT');

% 4-point DFT
N = 4; k = 0:N-1;
H2 = fft(h,N);
magH2 = abs(H2); phaH2 = angle(H2)*180/pi; % phase in degree
figure(4);
subplot(2,1,1);plot(w*N/(2*pi), magH, '--'); % w: 0 ~ 2*pi
axis([0,N,-1,7]); hold on
stem(k,magH2);
xlabel('k'); ylabel('|H2(K)|');
title('Magnitude of the 4-point DFT');
hold off;
subplot(2,1,2);plot(w*N/(2*pi), phaH, '--'); % w: 0 ~ 2*pi
axis([0,N,-180,180]); hold on
stem(k,phaH2);
xlabel('k'); ylabel('Degree');
title('Angle of the 4-point DFT');
hold off;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Zero-padding Example
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% 16-point DFT (12 zerod are padded)
x = [h,zeros(1,8)];
N = 16; k = 0:N-1;
X = fft(x,N);
magX = abs(X); phaX = angle(X)*180/pi;
figure(5);
subplot(2,1,1); plot(w*N/(2*pi),magH,'--');
axis([0,N,-1,7]); hold on
stem(k,magX);
xlabel('k'); ylabel('|X(k)|');
title('Magnitude of the 16-point DFT');
hold off
subplot(2,1,2); plot(w*N/(2*pi),phaH,'--');
axis([0,N,-180,180]); hold on
stem(k,phaX);
xlabel('k'); ylabel('Degree');
title('Angle of the 16-point DFT');
hold off