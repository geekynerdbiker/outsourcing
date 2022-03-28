clear; close all; clc

N=240;
xr=-0.5+(0.5+0.5).*rand(N, 1);  % rand() 함수 사용. (-0.5, 0.5) uniform 분포

[input_x, Fs]=audioread('8k16bit.wav');
bp=11001;
x=input_x(bp:bp+N-1);

M=100;
n=0:N-1;
k=-2*M+1:2*M; w=(pi/M)*k;   % frequency: -2*pi ~ 2*pi

W=exp(-1i*pi/M*(k'*n));

figure(1);

Xr=W*xr;    % 랜덤신호 xr의 DTFT
X=W*x;      % 음성신호 x의 DTFT 
subplot(2,2,1); plot(xr);
subplot(2,2,2); plot(x);
subplot(2,2,3); plot(w/pi, abs(Xr')); grid; axis([-2,2,0,10]);
xlabel('frequency in pi units'); ylabel('|Xr|');
title('Magnitude of Xr');
subplot(2,2,4); plot(w/pi, abs(X')); grid; axis([-2,2,0,10]);
xlabel('frequency in pi units'); ylabel('|X|');
title('Magnitude of X');

y=x; m=n+10;    % time shift: 10 samples
W=exp(-1i*pi/M*(k'*n)); % 변환 행렬
Y=W*y;          % DTFT of y

figure(2);
subplot(2,1,1); plot(n,x);
subplot(2,1,2); plot(m,y);

figure(3);
subplot(2,2,1); plot(w/pi, abs(X)); grid; axis([-2,2,0,10]);
xlabel('frequency in pi units'); ylabel('|X|');
title('Magnitude of X');
subplot(2,2,2); plot(w/pi, angle(X)/pi); grid; axis([-2,2,-1,1]);
xlabel('frequency in pi units'); ylabel('rediands/pi');
title('Angle of X');
subplot(2,2,3); plot(w/pi, abs(Y)); grid; axis([-2,2,0,10]);
xlabel('frequency in pi units'); ylabel('|Y|');
title('Magnitude of Y');
subplot(2,2,4); plot(w/pi, angle(Y)/pi); grid; axis([-2,2,-1,1]);
xlabel('frequency in pi units'); ylabel('|X|');
title('Angle of X');

y=exp(1i*pi/M).*x;  % multipled by a complex exponential signal
W=exp(-1i*pi/M*(k'*n)); % 변환 행렬
Y=W*y;              % DTFT of y

figure(4);
subplot(2,2,1); plot(w/pi, abs(X)); grid; axis([-2,2,0,10]);
xlabel('frequency in pi units'); ylabel('|X|');
title('Magnitude of X');
subplot(2,2,2); plot(w/pi, angle(X)/pi); grid; axis([-2,2,-1,1]);
xlabel('frequency in pi units'); ylabel('rediands/pi');
title('Angle of X');
subplot(2,2,3); plot(w/pi, abs(Y)); grid; axis([-2,2,0,10]);
xlabel('frequency in pi units'); ylabel('|Y|');
title('Magnitude of Y');
subplot(2,2,4); plot(w/pi, angle(Y)/pi); grid; axis([-2,2,-1,1]);
xlabel('frequency in pi units'); ylabel('rediands/pi');
title('Angle of Y');