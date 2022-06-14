function out = SobelEdge(im)

[H,W] = size(im);
channel = size(im,3);

Gx = [1 0 -1; 2 0 -2; 1 0 -1];
Gy = [1 +2 +1; 0 0 0; -1 -2 -1];

for i=1:H
    for j=1:W
        for k=1:channel
            if i-1<1 ; i=i+1; end
            if j-1<1 ; j=j+1; end
            if i+1>size(im,1); i=size(im,1)-1; end
            if j+1>size(im,2); j=size(im,2)-1; end

            origin = im(i-1:i+1, j-1:j+1, k);
            convX=sum(Gx.*origin);
            x=sum(convX);
            convY=sum(Gy.*origin);
            y=sum(convY);

            pixValue=sqrt(x.^2 + y.^2);

            out(i,j,k)=pixValue;
        end
    end
end

end