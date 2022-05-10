function out = medianFiltering(im, filterSize)

[H,W] = size(im);
median_img = zeros(H,W);
a= filterSize(1,1);
b= filterSize(1,2);
a2 = floor(a/2);
b2 = floor(b/2);

for i=1 : H
    for j= 1 : W
        s=1;
        if s<=a
            for x = -a2:a2
                for y= -b2:b2
                    if i+x <1; x=1-i; end
                    if j+y <1; y=1-j; end
                    if i+x > size(im,1); x=size(im,1)-i; end
                    if j+y > size(im,1); y=size(im,2)-j; end
                    Mask(s) = im(i+x,j+y);
                    s=s+1;
                end
            end
        end

        for k = 2 : a
            if s<=k*a && s>(K-1)*a
                for x = -a2:a2
                    for y= -b2:b2
                        if i+x <1; x=1-i; end
                        if j+y <1; y=1-j; end
                        if i+x > size(im,1); x=size(im,1)-i; end
                        if j+y > size(im,1); y=size(im,2)-j; end
                        Mask(s) = im(i+x,j+y);
                        s=s+1;
                    end
                end
            end
        end
        med = sort(Mask);
        new_pixel = med(floor(a*b/2));
        median_img(i,j) = new_pixel;
    end
end
out = median_img/255;
end