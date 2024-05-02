function x = solve_heat(a, b, dt, dx, alpha, theta, ic, t_final)
    n = length(ic);
    [M, R] = create_matrices(n, alpha * dt / dx.^2, theta, dx);
    un = ic;

    for t = 1:t_final / dt
        b = R * un + a * ones(n) + b * ones(n);
        x = tridiag_solve(M, R, b, ic.');
        un = x;
    end
    x=un;
end
