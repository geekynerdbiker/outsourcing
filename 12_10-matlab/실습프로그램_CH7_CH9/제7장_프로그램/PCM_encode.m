function [pcm_encode] = PCM_encode(x, n)


y = x - min(x);

norm_factor = max(y);               % Normalization Factor;

y = (y*(2^(n)-1))/norm_factor;

y = round(y);

temp = y;
pcm_encode = zeros(n, length(x));

for ii = 1:n
    pcm_encode(ii, :) = mod(temp, 2);
    temp = fix(temp/2);
end
pcm_encode = pcm_encode(end:-1:1,:);
