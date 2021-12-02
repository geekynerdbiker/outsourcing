function [x_q] = quantization(x, n, normalization_flag)

min_x = -(2^(n-1)-1);
max_x = 2^(n-1);

A = max(abs(x));        % Normalization factor;
if normalization_flag == 0
    x = x./A;
end
x_q = x;
x_q = x_q.*(2^(n-1));

x_q = x_q + 0.5;
x_q = round(x_q);

x_q(x_q <= min_x) = min_x;
x_q(x_q >= max_x) = max_x;

x_q = x_q - 0.5;

x_q = x_q./(2^(n-1));


