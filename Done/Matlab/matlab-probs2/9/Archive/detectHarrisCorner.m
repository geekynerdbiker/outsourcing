function [corner, C] = detectHarrisCorner(im, fx_operator, fy_operator, Gaussian_sigma, alpha, C_thres, NMS_ws)

im = rgb2gray(im);
im = im2double(im);

[H,W] = size(im);

fx = conv2(im,fx_operator,'same');
fy = conv2(im,fy_operator,'same');

g = gaussianFiltering(Gaussian_sigma);
    function out = gaussianFiltering(Gaussian_sigma)
        filterSize = 2*ceil(2*Gaussian_sigma)+1;
        halfFs = floor(filterSize/2);
        weight = zeros(filterSize, filterSize);
        for y =-halfFs:halfFs
            for x = -halfFs : halfFs
                weight(y+halfFs+1,x+halfFs+1) = exp(-(y.^2+x.^2) / (2*Gaussian_sigma^2));
            end
        end
        out=weight/sum(weight,'all');
    end

g_fx2 = conv2(fx.^2, g, 'same');
g_fy2 = conv2(fy.^2, g, 'same');
g_fxfy = conv2(fx.*fy, g, 'same');

C = g_fx2.*g_fy2 - g_fxfy.^2-alpha*(g_fx2 + g_fy2).^2;

cor_a = 1;
C_thres = C_thres*max(C);

for b = 1+4:H-4
    for a = 1+4:W-4
        if (C(b,a) > C_thres)
            field = zeros(NMS_ws,NMS_ws);
            for j = -floor(NMS_ws/2) : floor(NMS_ws/2)
                for i = -floor(NMS_ws/2) : floor(NMS_ws/2)
                    field(j+4,i+4) = C(b+j, a+i);
                end
            end
            localMax_C = max(field,[],'all');
            if(C(b,a) == localMax_C)
                corner(cor_a, :) = [a b];
                cor_a = cor_a + 1;
            end
        end
    end
end

end
