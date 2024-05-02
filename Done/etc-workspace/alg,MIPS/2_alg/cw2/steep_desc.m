function [x, N] = steep_desc(f, grad, x, gamma, epsilon, max_iter)

  N = 0;
  while N < max_iter
    grad_x = grad(x);
    if norm(grad_x) < epsilon
      break;
    end

    d = -gamma * grad_x;
    x = x + d;
    N = N + 1;
  end

end