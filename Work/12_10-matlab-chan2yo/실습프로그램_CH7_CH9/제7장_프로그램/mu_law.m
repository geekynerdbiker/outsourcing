function [y, K] = mu_law(x, mu)

if nargin == 1
    mu = 255;
end

K = max(abs(x));
y = (log(1+mu*abs(x./K))./log(1+mu)).*sign(x);

