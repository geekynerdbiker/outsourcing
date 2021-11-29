close all;  clear;
Rb = 1000;
fs = 16*Rb;

% Line code waveform
b =[ 1 0 1 0 1 1];
subplot(411), [x, t] = linecode_gen(b, 'polar_nrz', Rb, fs); waveform(x, fs)
ylabel('polar nrz');
subplot(412), [x, t] = linecode_gen(b, 'unipolar_rz', Rb, fs); waveform(x, fs)
ylabel('unipolar rz');
subplot(413), [x, t] = linecode_gen(b, 'bipolar_rz', Rb, fs); waveform(x, fs)
ylabel('bipolar rz');
subplot(414), [x, t] = linecode_gen(b, 'manchester', Rb, fs); waveform(x, fs)
ylabel('manchester');
disp('hit any key to see PSD'); pause

% Power spectral density
b = random_seq(2000);
figure;
subplot(221), [x, t] = linecode_gen(b, 'unipolar_nrz', 1000, fs);
   psd_est(x,fs, 'decibel'); %axis([0 8 10^(-9) 10^(-1)]);
   title('Unipolar NRZ (R_b = 1 kbps)')
subplot(222), [x, t] = linecode_gen(b, 'unipolar_nrz', 2000, fs); ...
   psd_est(x,fs, 'decibel'); %axis([0 8 10^(-9) 10^(-1)]);
   title('Unipolar NRZ (R_b = 2 kbps)')

subplot(223), [x, t] = linecode_gen(b, 'manchester', 1000, fs); 
   psd_est(x,fs, 'decibel'); %axis([0 8 10^(-9) 10^(-1)]);
   title('Manchester (R_b = 1 kbps)')
subplot(224), [x, t] = linecode_gen(b, 'manchester', 2000, fs); 
   psd_est(x,fs, 'decibel'); %axis([0 8 10^(-9) 10^(-1)]);
   title('Manchester (R_b = 2 kbps)')
