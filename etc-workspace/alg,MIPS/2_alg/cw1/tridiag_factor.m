function [l, d, u] = tridiag_factor(T)
    n = length(T);
    l = ones(n - 1, 1);
    d = T(1);
    u = zeros(n - 1, 1);

    for i = 2:n
        d(i) = T(i, i) - l(i - 1) * u(i - 1);
        u(i) = T(i, i - 1) / d(i);
    end
end
