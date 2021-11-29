clear; close all;

load speech_sample samples Fs;

time = 1/Fs:1/Fs:10;
x = samples;
%sound(x, Fs);  % Original voice
% -------------------------------------------------------------------------
AXIS_TIME = [-inf inf -0.3 0.3];
figure
plot(time, x); grid on; axis(AXIS_TIME);
xlabel('time [sec]'); title('Original Voice Signal');
% -------------------------------------------------------------------------
n = 6;
str_n = num2str(2^n);
x_qu = quantization(x, n, 1);
% -------------------------------------------------------------------------

figure
plot(time, x_qu); grid on; axis(AXIS_TIME);
xlabel('time [sec]'); title([str_n, ' Level Uniform Quantization']);
% -------------------------------------------------------------------------
[x_comp, K] = mu_law(x, 255);
x1 = quantization(x_comp, n, 0);
x2 = inv_mu_law(x1);
x_qn = x2*K;

figure
plot(time, x_qn); grid on; axis(AXIS_TIME);
xlabel('time [sec]'); title([str_n, ' Level Non-Uniform Quantization']);
% -------------------------------------------------------------------------

SQNR_uniform = 20*log10(norm(x)/norm(x-x_qu))
SQNR_nonuniform = 20*log10(norm(x)/norm(x-x_qn))
%disp('Press a key if you want hear the uniformly quantized voice'); pause  
%sound(x_qu, Fs);  % Uniformly quantized voice
%disp('Press a key if you want hear the nonuniformly quantized voice'); pause
%sound(x_qn, Fs);  % Nonuniformly quantized vice

