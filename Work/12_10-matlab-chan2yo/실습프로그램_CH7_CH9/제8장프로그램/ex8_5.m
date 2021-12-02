clear; close all;
% -------------------------------------------------------------------------
%  Raised cosine pulse shaping
% -------------------------------------------------------------------------
Rb = 1; fs = 100*Rb;
Tb = 1/Rb; ts = 1/fs;
df = 0.01;

roll_off = [0, 0.5, 1];  % Roll-off factor
[Hf1, freq1] = raised_cosine_freq(Rb, df, roll_off(1));
[Hf2, freq2] = raised_cosine_freq(Rb, df, roll_off(2));
[Hf3, freq3] = raised_cosine_freq(Rb, df, roll_off(3));
% -------------------------------------------------------------------------
str1 = ['Roll-off = ',num2str(roll_off(1))];
str2 = ['Roll-off = ',num2str(roll_off(2))];
str3 = ['Roll-off = ',num2str(roll_off(3))];
% -------------------------------------------------------------------------
freq_vec = [-1.5*Rb 1.5*Rb 0 1.5];
figure
plot(freq1, Hf1, 'k'), hold on;
plot(freq2, Hf2, 'b'), hold on;
plot(freq3, Hf3, 'r'), hold on;
grid on; axis(freq_vec);
xlabel('frequency [Hz]'); title('Frequency Response of Raised Cosine Filter');
legend(str1, str2, str3);
% -------------------------------------------------------------------------
[ht1, time1] = raised_cosine_time(Rb, fs, roll_off(1));
[ht2, time2] = raised_cosine_time(Rb, fs, roll_off(2));
[ht3, time3] = raised_cosine_time(Rb, fs, roll_off(3));
% -------------------------------------------------------------------------
time_vec = [-5*Tb, 5*Tb, -0.5 1.2];
figure
plot(time1, ht1, 'k'); hold on;
plot(time2, ht2, 'b'); hold on;
plot(time3, ht3, 'r'); hold on;
grid on; axis(time_vec);
xlabel('time [sec]'); title('Impulse Response of Raised Cosine Filter');
legend(str1, str2, str3);
% -------------------------------------------------------------------------
