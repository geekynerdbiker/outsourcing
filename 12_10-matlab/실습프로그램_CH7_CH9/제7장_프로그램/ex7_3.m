clear; close all;
ts = 0.001;
fs = 1 / ts;
T1 = -1; T2 = 1;
time = T1:ts:T2;
% -------------------------------------------------------------------------
f = 1;
x = sin(2*pi*f*time);
% -------------------------------------------------------------------------
AXIS_TIME1 = [-inf inf -1.2 1.2];
AXIS_TIME2 = [-inf inf -0.15 0.15];
% -------------------------------------------------------------------------
n = 3;               % Quantization Bits;
[x_q] = quantization(x, n, 0);

str_n = num2str(n);

figure
plot(time, x, 'b'); hold on;
plot(time, x_q, 'r-'); hold on;
xlabel('time [sec]'); title(['Uniform Quantization with ', str_n,' bits']);
grid on; axis(AXIS_TIME1);

figure
plot(time, x-x_q, 'b-'); hold on;
xlabel('time [sec]'); title(['Quantization Noise for ', str_n,' bit quantizer']);
grid on; axis(AXIS_TIME2);

SQNR = 20*log10(norm(x)/norm(x - x_q))
% -------------------------------------------------------------------------
n = 4;                  % Quantization Bits;
[x_q] = quantization(x, n, 0);

str_n = num2str(n);

figure
plot(time, x, 'b'); hold on;
plot(time, x_q, 'r-'); hold on;
xlabel('time [sec]'); title(['Uniform Quantization with ', str_n,' bits']);
grid on; axis(AXIS_TIME1);

figure
plot(time, x-x_q, 'b-'); hold on;
xlabel('time [sec]'); title(['Quantization Noise for ', str_n,' bit quantizer']);
grid on; axis(AXIS_TIME2);

SQNR = 20*log10(norm(x)/norm(x - x_q))
% -------------------------------------------------------------------------
