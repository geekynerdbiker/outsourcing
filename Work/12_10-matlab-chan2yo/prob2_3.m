L=20;
R=1.0e4;
Fs=8*R;
T=1/R;
Ts=1/Fs;
alpha =1;

if mod(L, 2)==0 
 M=L/2;
else
 M=(L-1)/2;
end 
g=zeros(1,L);
for n=-M:M 
 num=sin(pi*n*Ts/T)*cos(alpha*pi*n*Ts/T);
 den=(pi*n*Ts/T)*(1-(2*alpha*n*Ts/T)^2);
 g(n+M+1)=num/den; 
 if (1-(2*alpha*n*Ts/T)^2)==0 
 g(n+M+1)=pi/4*sin(pi*n*Ts/T)/(pi*n*Ts/T);
 end 
 if (pi*n*Ts/T)==0 
 g(n+M+1)=cos(alpha*pi*n*Ts/T)/(1-(2*alpha*n*Ts/T)^2); 
 end 
end 

data1 = round(rand(1,20));
data2 = (-2*data1) + 1;
output1=upsample(data1,Fs/R);
output2=upsample(data2,Fs/R);

y1=filter(g,1,output1);
y2=filter(g,1,output2);

[b,a]=butter(5,[25 25]/Fn, 'bandpass');
y2=filter(b,a,y1)

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