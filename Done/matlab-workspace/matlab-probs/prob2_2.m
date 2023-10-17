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
output1=upsample(data1,Fs/R);

y1=filter(g,1,output1);

Fn=1e3
[b,a]=butter(5,[25 25]/Fn, 'bandpass');
fx=filter(b,a,y1)

figure;
plot(fx);
stem(data1);
title('Input data to the Raised Cosine Filter');
ylim([-1 ,2]);
xlabel('Samples');
ylabel('Amplitude');
disp('hit any key to see the spectrum'); pause  

Fn=Fs/2;NFFY=2.^(ceil(log(length(y1))/log(2)));
FFTY=fft(y1,NFFY);
NumUniquePts=ceil((NFFY+1)/2); 
FFTY=FFTY(1:NumUniquePts);
MY=abs(FFTY);
MY=MY*2;
MY(1)=MY(1)/2;
MY(length(MY))=MY(length(MY))/2;
MY=MY/length(y1);
f1=(0:NumUniquePts-1)*2*Fn/NFFY;

figure;
plot(f1,20*log10(abs(MY).^2));xlabel('FREQUENCY(Hz)');ylabel('DB');
grid
title('Frequency domain plots') 
disp('hit any key to see the spectrum'); pause  