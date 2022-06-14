R=1.0e4;
Fs=8*R;
T=1/R;
Tfs=1/Fs;
a =1;

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

data = round(rand(1,20)); 
out = upsample(data,Fs/R);
fx=filter(graph,1,out);

figure;
plot(fx);
stem(data);
title('Input data to the Raised Cosine Filter');
xlabel('Samples');
ylabel('Amplitude');
ylim([-1 ,2]);

Fn=Fs/2;
NFFY=2.^(ceil(log(length(fx))/log(2)));
FFT_Y=fft(fx,NFFY);
NUP=ceil((NFFY+1)/2); 
FFT_Y=FFT_Y(1:NUP);
MY_FUNC=abs(FFT_Y);
MY_FUNC=MY_FUNC*2;
MY_FUNC(1)=MY_FUNC(1)/2;
MY_FUNC(length(MY_FUNC))=MY_FUNC(length(MY_FUNC))/2;
MY_FUNC=MY_FUNC/length(fx);
func=(0:NUP-1)*2*Fn/NFFY;

figure;
plot(func, 20*log10(abs(MY_FUNC).^2));
xlabel('FREQUENCY(Hz)');
ylabel('DB');
grid
title('Frequency domain plots') 