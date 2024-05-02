function x = tridiag_solve(l, d, u, c)
    n = length(c);
    x = zeros(n, 1);
    x(1) = c(1) / d(1);

    for i = 2:n
        x(i) = (c(i) - l(i - 1) * x(i - 1)) / d(1);
    end

end
