R=1.0e4;
Fs=8*R;

T=1/R;
Tfs=1/Fs;

a=1;

if mod(20, 2)==0 modula=20/2;
else modula=(20-1)/2;
end 

graph=zeros(1,20);
for n=-modula:modula 
    d=(pi*n*Tfs/T)*(1-(2*n*a*Tfs/T)^2);
    num=cos(pi*n*a*Tfs/T)*sin(pi*n*Tfs/T);
    graph(n+modula+1)=num/d; 
    
    if (1-(2*n*a*Tfs/T)^2)==0 graph(n+modula+1)=pi/4*sin(pi*n*Tfs/T)/(pi*n*Tfs/T);
    end

    if (pi*n*Tfs/T)==0 graph(n+modula+1)=cos(pi*n*a*Tfs/T)/(1-(2*n*a*Tfs/T)^2); 
    end 
end 

data1 = round(rand(1,20));
data2 = (-2*data1) + 1;
output1=upsample(data1,Fs/R);
output2=upsample(data2,Fs/R);

y1=filter(g,1,output1);
fx=filter(g,1,output2);

[b,a]=butter(5,[25 25]/Fn, 'bandpass');
fx=filter(b,a,y1)

figure;
subplot(2,1,1);
stem(data1);
title('Input data to the Raised Cosine Filter');
xlabel('Samples');
ylabel('Amplitude');
subplot(2,1,2);
plot(y1);
title('Response of the Raised Cosine Filter for the given Input');
xlabel('Samples');
ylabel('Amplitude');
disp('hit any key to see the spectrum'); pause  