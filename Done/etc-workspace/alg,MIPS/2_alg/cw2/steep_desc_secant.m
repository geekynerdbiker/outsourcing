function [x, N] = steep_desc_secant(f, grad, x, epsilon, max_iter)

  N = 0;
  while N < max_iter
    grad_x = grad(x);
    d = -grad_x;
    alpha = linesearch_secant(grad, x, d, epsilon, max_iter);
    x = x + alpha * d;
    N = N + 1;
  end

end