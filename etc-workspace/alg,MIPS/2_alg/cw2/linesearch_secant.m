function alpha = linesearch_secant(grad, x, d, epsilon, max_iter)

  alpha0 = 0;
  alpha1 = 0.001;

  for i = 1:max_iter
    f_x = feval(grad, x);
    f_x_plus_alpha_d = feval(grad, x + alpha1 * d);

    grad_x = feval(grad, x);
    grad_x_plus_alpha_d = feval(grad, x + alpha1 * d);

    if abs(d' * (grad_x_plus_alpha_d - grad_x)) < epsilon * abs(d' * grad_x)
      alpha = alpha1;
      break;
    end

    alpha0 = alpha1;
    alpha1 = (alpha1 - alpha0) * (f_x_plus_alpha_d - f_x) / (d' * (grad_x_plus_alpha_d - grad_x));
  end

  if i == max_iter
    error('Line search did not converge in max_iter iterations');
  end

end