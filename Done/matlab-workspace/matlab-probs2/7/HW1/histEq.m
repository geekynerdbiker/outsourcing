function result = histEq(im)

[height, width, ~] = size(im);
hist = zeros(1, 256);

for row = 1:height
    for col = 1:width
        hist(im(row,col)) = hist(im(row,col))+1;
    end
end

hist = hist/(width*height);

cdf = zeros(1, 256);
cdf(1) = hist(1);

for row = 2:256
    cdf(row) = cdf(row-1)+hist(row);
end

result = roundn(cdf(im)*256, 0);