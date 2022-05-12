function out=gaussianFiltering(im,sigma)

filterSize = 2*ceil(2*sigma)+1;
halfFs = floor(filterSize/2);

weight = zeros(filterSize, filterSize);

for y =-halfFs:halfFs
    for x = -halfFs : halfFs
        weight(y+halfFs+1,x+halfFs+1) = 1/(2*pi*sigma^2) * exp(-(y^2+x^2) / (2*sigma^2));
    end
end

weight = weight / sum(weight, 'all');

out = zeros(size(im));
[filH,filW] = size(weight);
halfH = floor(filH / 2);
halfW = floor(filW / 2);

    for y2 = 1:size(im,1)
        for x2 = 1:size(im,2)
            for s = -halfH:halfH
                for t = -halfW:halfW
                    ys=y2-s;
                    xt=x2-t;
                    if ys<1 ; ys=1; 
                    end
                    if xt<1 ; xt=1;
                    end
                    if ys > size(im,1); ys = size(im,1);
                    end
                    if xt > size(im,2); xt = size(im,2);
                    end
                    out(y2,x2) = out(y2,x2) + weight(s + halfH + 1,t + halfW +1) * im(ys,xt);
                end
            end
        end
    end
end