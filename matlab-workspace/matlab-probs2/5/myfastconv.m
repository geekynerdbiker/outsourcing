function y = myfastconv(x, h)
% Fast Convolution
% Convolves x and h
% x = input vector
% h = input vector
%
Ly=length(x)+length(h)-1; % Length of y
Ly2=pow2(nextpow2(Ly)); % Find smallest power of 2 that is > Ly
sss = sprintf('Ly = %d + %d - 1 = %d', length(x), length(h), Ly); disp(sss);
sss = sprintf('nextpow2(%d) = %d', Ly, nextpow2(Ly)); disp(sss);
sss = sprintf('Ly2 = 2^%d = %d', nextpow2(Ly), Ly2); disp(sss);
X=fft(x, Ly2); % Fast Fourier transform
H=fft(h, Ly2); % Fast Fourier transform
Y=X.*H; % Multiplication in frequency domain
y=ifft(Y); % Inverse fast Fourier transform
y=y(1:Ly); % Take just the first Ly elements