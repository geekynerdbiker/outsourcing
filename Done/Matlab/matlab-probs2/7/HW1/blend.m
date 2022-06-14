function result = blend(im1, im2, alpha)
result = alpha.*im1 + (1-alpha).*im2
