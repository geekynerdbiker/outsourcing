% 1.1
n=[0:31]
X=sin(2*pi*220*n/2048)
stem(X)

%1.2
X=fft(X);
stem(abs(X));
ylabel("|X|")
ylim([0 17])
xlabel("Frequency(Hz)")
xlim([1 17])
xticks([n])
xticklabels((n-1)*64)

% 1.4
n=[0:512]
X=sin(2*pi*220*n/2048)

%1.5
X=fft(X);
stem(abs(X));
ylabel("|X|")
xlabel("Frequency(Hz)")
xlim([1 257])
xticks([n])
xticklabels((n-1)*64)