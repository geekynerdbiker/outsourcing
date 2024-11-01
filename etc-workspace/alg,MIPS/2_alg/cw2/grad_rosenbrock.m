function grad = grad_rosenbrock(x)

  grad = [-200 * x(1) * (x(2) - x(1)^2) - 2 * (1 - x(1)),
          200 * (x(2) - x(1)^2)];

end