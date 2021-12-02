clear; close all;
% -------------------------------------------------------------------------
% Raised cosine pulse shaping
% -------------------------------------------------------------------------
Rb = 1;     fs = 16*Rb;
Tb = 1/Rb;  ts = 1/fs;
Nbit = fs/Rb;  % Number of samples per bit
% -------------------------------------------------------------------------
bitlen = 10^4;
bit = randi([0,1], 1, bitlen);
bit(bit==0) = -1;
% bit = rand(1, bitlen);
% bit = 2*round(bit)-1;
p = zeros(1, Nbit); p(1) = 1;
bt = bit'*p;
%bt = bit'*ones(1, Nbit);
bt = bt';   bt = bt(:)';
x = bt;
N_data = length(x);
% -------------------------------------------------------------------------
Ttime = 0:ts:bitlen*Tb-ts;
time_vec = [0, 20*Tb, -2, 2];
% -------------------------------------------------------------------------
ht0 = ones(1, Nbit); % Rectangular pulse shape
roll_off = [0, 0.5, 1];
[ht1, time1] = raised_cosine_time(Rb, fs, roll_off(1));
[ht2, time2] = raised_cosine_time(Rb, fs, roll_off(2));
[ht3, time3] = raised_cosine_time(Rb, fs, roll_off(3));
delay = floor(length(time1)/2); 
% -------------------------------------------------------------------------
xt0 = conv(x, ht0); xt0 = xt0(1:N_data);
xt1 = conv(x, ht1); xt1 = xt1(delay:(delay+N_data-1));
xt2 = conv(x, ht2); xt2 = xt2(delay:(delay+N_data-1));
xt3 = conv(x, ht3); xt3 = xt3(delay:(delay+N_data-1));
% -------------------------------------------------------------------------
noise_power = 0;
f_cutoff = 0.75*Rb;        % Channel bandwidth

y = channel_filter(xt0, 1, noise_power, f_cutoff, fs);
yt0 = y(1:length(xt0));

yt1 = channel_filter(xt1, 1, noise_power, f_cutoff, fs);
yt2 = channel_filter(xt2, 1, noise_power, f_cutoff, fs);
yt3 = channel_filter(xt3, 1, noise_power, f_cutoff, fs);
% -------------------------------------------------------------------------
figure
subplot(211), stairs(Ttime, xt0); grid on; axis(time_vec);
xlabel('time [sec]'); title('Rectangular');
subplot(212), plot(Ttime, yt0); grid on; axis(time_vec);
xlabel('time [sec]'); title(['Channel Output, cut-off freq = ',num2str(f_cutoff)]);

figure
subplot(211), plot(Ttime, xt1); grid on; axis(time_vec);
xlabel('time [sec]'); title(['Raised Cosine, roll-off = ', num2str(roll_off(1))]);
subplot(212), plot(Ttime, yt1); grid on; axis(time_vec);
xlabel('time [sec]'); title(['Channel Output, cut-off freq = ',num2str(f_cutoff)]);

figure
subplot(211), plot(Ttime, xt2); grid on; axis(time_vec);
xlabel('time [sec]'); title(['Raised Cosine, roll-off = ', num2str(roll_off(2))]);
subplot(212), plot(Ttime, yt2); grid on; axis(time_vec);
xlabel('time [sec]'); title(['Channel Output, cut-off freq = ',num2str(f_cutoff)]);

figure
subplot(211), plot(Ttime, xt2); grid on; axis(time_vec);
xlabel('time [sec]'); title(['Raised Cosine, roll-off = ', num2str(roll_off(3))]);
subplot(212), plot(Ttime, yt2); grid on; axis(time_vec);
xlabel('time [sec]'); title(['Channel Output, cut-off freq = ',num2str(f_cutoff)]);

% -------------------------------------------------------------------------
[Sx0, freq] = psd_est(xt0, fs, 'decibel');
[Sx1, freq1] = psd_est(xt1, fs, 'decibel');
[Sx2, freq2] = psd_est(xt2, fs, 'decibel');
[Sx3, freq3] = psd_est(xt3, fs, 'decibel');
% -------------------------------------------------------------------------
feq_vec = [0, 5*Rb, -80, 0];

str1 = ['RC roll-off=',num2str(roll_off(1))];
str2 = ['RC roll-off=',num2str(roll_off(2))];
str3 = ['RC roll-off=',num2str(roll_off(3))];

figure
plot(freq, Sx0, 'k'); hold on;
plot(freq1, Sx1, 'b'); hold on;
plot(freq2, Sx2, 'm'); hold on;
plot(freq3, Sx3, 'r'); hold on;
grid on; axis(feq_vec);
xlabel('Normalized frequency'); ylabel('PSD [dB]');
title('Channel Input');
legend('Rect',str1,str2,str3);

% -------------------------------------------------------------------------
[Sy0, freq_y0] = psd_est(yt0, fs, 'decibel');
[Sy1, freq_y1] = psd_est(yt1, fs, 'decibel');
[Sy2, freq_y2] = psd_est(yt2, fs, 'decibel');
[Sy3, freq_y3] = psd_est(yt3, fs, 'decibel');
% -------------------------------------------------------------------------
figure
plot(freq_y0, Sy0, 'k'); hold on;
plot(freq_y1, Sy1, 'b'); hold on;
plot(freq_y2, Sy2, 'm'); hold on;
plot(freq_y3, Sy3, 'r'); hold on;
grid on; axis(feq_vec);
xlabel('Normalized frequency'); ylabel('PSD [dB]');
title(['Channel Output (bandwidth = ', num2str(f_cutoff), ' )']);
legend('Rect',str1,str2,str3);