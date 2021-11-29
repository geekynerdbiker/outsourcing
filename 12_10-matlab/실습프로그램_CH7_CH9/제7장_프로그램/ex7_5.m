clear all; close all;

% -------------------------------------------------------------------------
x = randn(1, 1000);     % To Generate a Gaussian Noise
A = max(abs(x));        % Normalization Factor;
x = x./A;
% -------------------------------------------------------------------------
AXIS1 = [-inf inf -0.08, 0.08];
AXIS2 = [-1, 1, -1, 1];
% -------------------------------------------------------------------------
n = 4;
str_n = num2str(2^n);

x_q = quantization(x, n, 1);

figure
plot(x - x_q);
xlabel('samples'); title(['Quantization Noise for ',str_n,' Level Quantizer']);
grid on; axis(AXIS1);

[y, index] = sort(x);

figure
plot(y, x_q(index));
xlabel('input value'); ylabel('quantized value'); title(['Quantization value vs. input value, for ',str_n,' Level Quantizer']);
grid on; axis(AXIS2);

SQNR = 20*log10(norm(x)/norm(x-x_q))
sprintf('SQNR = %0.5g',SQNR);
code2 = PCM_encode(x_q, n);
code2(:, 1:5)
% -------------------------------------------------------------------------