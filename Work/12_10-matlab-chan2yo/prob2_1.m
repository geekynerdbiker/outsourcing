L=20;
R=1.0e4;
Fs=8*R;
T=1/R;
Ts=1/Fs;
alpha =1;

if mod(L, 2)==0 
 M=L/2 ;
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

data = round(rand(1,20)); 
output=upsample(data,Fs/R);
y=filter(g,1,output);

figure;
plot(y);
stem(data);
title('Input data to the Raised Cosine Filter');
ylim([-1 ,2]);
xlabel('Samples');
ylabel('Amplitude');
disp('hit any key to see the spectrum'); pause  

Fn=Fs/2;NFFY=2.^(ceil(log(length(y))/log(2)));
FFTY=fft(y,NFFY);
NumUniquePts=ceil((NFFY+1)/2); 
FFTY=FFTY(1:NumUniquePts);
MY=abs(FFTY);
MY=MY*2;
MY(1)=MY(1)/2;
MY(length(MY))=MY(length(MY))/2;
MY=MY/length(y);
f=(0:NumUniquePts-1)*2*Fn/NFFY;

figure;
plot(f,20*log10(abs(MY).^2));xlabel('FREQUENCY(Hz)');ylabel('DB');
grid
title('Frequency domain plots') 
disp('hit any key to see the spectrum'); pause  