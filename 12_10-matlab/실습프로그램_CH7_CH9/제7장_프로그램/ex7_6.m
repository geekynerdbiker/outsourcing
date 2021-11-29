clear; close all;
x = randn(1, 1000);     % To Generate a Gaussian Noise
AXIS1 = [-inf inf -1, 1];
AXIS2 = [-1, 1, -1, 1];
% -------------------------------------------------------------------------
n = 6;  % Quantization bits per sample
str_n = num2str(2^n);
% -------------------------------------------------------------------------
[x_comp, K] = mu_law(x, 255);
x1 = quantization(x_comp, n, 1);
x2 = inv_mu_law(x1);
x_qc = x2*K;

figure
plot(x-x_qc);
xlabel('samples'); title(['Quantization Noise for ',str_n,' Level Non-Uniform Quantizer']);
grid on; axis(AXIS1);

[z, index] = sort(x);

figure
plot(z, x_qc(index));
xlabel('input value'); ylabel('quantized value'); title(['Quantization value vs. input value, for ',str_n,' Level Quantizer']);
grid on; axis(AXIS2);

SQNR = 20*log10(norm(x)/norm(x-x_qc))

% -------------------------------------------------------------------------
n = 4;   % Quantization bits per sample
str_n = num2str(2^n);
% -------------------------------------------------------------------------
[x_comp, K] = mu_law(x, 255);
x1 = quantization(x_comp, n, 1);
x2 = inv_mu_law(x1);
x_qc = x2*K;

figure
plot(x-x_qc);
xlabel('samples'); title(['Quantization Noise for ',str_n,' Level Non-Uniform Quantizer']);
grid on; axis(AXIS1);

[z, index] = sort(x);

figure
plot(z, x_qc(index));
xlabel('input value'); ylabel('quantized value'); title(['Quantization value vs. input value, for ',str_n,' Level Quantizer']);
grid on; axis(AXIS2);

SQNR = 20*log10(norm(x)/norm(x-x_qc))
% -------------------------------------------------------------------------