function [M, R] = create_matrices(n, lambda, theta, dx)
    A = eye(n - 1) - lambda * (1 - theta);
    M = A * dx^2 .* diag(ones(n - 1, 1));
    R = A + lambda * theta * dx^2 * diag(ones(n - 1, 1));
end
