function [l, d, u] = tridiag_factor(T)
    n = length(T);
    l = zeros(n - 1, 1);
    d = T(1);
    u = zeros(n - 1, 1);

    for i = 2:n
        l(i - 1) = T(i) - u(i - 1) * T(i - 1) / d;
        d(i) = T(i) - l(i - 1) * T(i - 1) / d;
        u(i - 1) = (T(i + 1) - d(i)) / l(i - 1);
    end
end

function x = tridiag_solve(l, d, u, c)
    n = length(c);
    x = zeros(n, 1);
    x(1) = c(1) / d(1);

    for i = 2:n
        x(i) = (c(i) - l(i - 1) * x(i - 1)) / d(i);
    end

    for i = n - 1:-1:1
        x(i) = x(i) - u(i - 1) * x(i + 1);
    end
end

function [M, R] = create_matrices(n, lambda, theta, dx)
    A = tridiag(-2, 1, 1, n - 1);
    M = eye(n) - lambda * (1 - theta) * A;
    R = eye(n) + lambda * theta * A;

    M(1, 1) = 1 - lambda * (1 - theta);
    M(n, n) = 1 - lambda * (1 - theta);
    R(1, 1) = 1 + lambda * theta;
    R(n, n) = 1 + lambda * theta;
end

function x = solve_heat(a, b, dt, dx, alpha, theta, ic, t_final)
    n = length(ic);
    M, R = create_matrices(n, alpha * dt / dx.^2, theta, dx);
    un = ic;

    for t = 1:t_final / dt
        b = R * un + a * ones(n) + b * ones(n);
        x = tridiag_solve(M, R, b);
        un = x;
    end
    x = un;
end
