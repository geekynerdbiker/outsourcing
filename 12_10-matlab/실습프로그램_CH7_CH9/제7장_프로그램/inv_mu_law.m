function y = inv_mu_law(x, mu)

if nargin == 1
    mu = 255;
end
y = (((1+mu).^(abs(x))-1)./mu).*sign(x);


