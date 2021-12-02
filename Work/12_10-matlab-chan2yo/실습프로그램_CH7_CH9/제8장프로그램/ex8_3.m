close all; clear;
Rb = 1000;
fs = 40*Rb;

% Eye diagram
b = random_seq(400);
[x, t] = linecode_gen(b, 'polar_nrz', Rb, fs);

% Bandlimited filter only
y = channel_filter(x, 1, 0.0, 2500, fs);
eye_diagram(y, Rb, fs);
pause; disp('Press any key to continue');
y = channel_filter(x, 1, 0.0, 1500, fs);
figure; eye_diagram(y, Rb, fs);
pause; disp('Press any key to continue');
y = channel_filter(x, 1, 0.0, 800, fs);
figure; eye_diagram(y, Rb, fs);
pause; disp('Press any key to continue');
y = channel_filter(x, 1, 0.0, 500, fs);
figure; eye_diagram(y, Rb, fs);
pause; disp('Press any key to continue');

% Filter and noise
b = random_seq(100);
[x, t] = linecode_gen(b, 'polar_nrz', Rb, fs);
close all
y = channel_filter(x, 1, 0.0, 800, fs);
eye_diagram(y, Rb, fs);
pause; disp('Press any key to continue');
y = channel_filter(x, 1, 0.05, 800, fs);
figure; eye_diagram(y, Rb, fs);
pause; disp('Press any key to continue');
y = channel_filter(x, 1, 0.1, 800, fs);
figure; eye_diagram(y, Rb, fs);
pause; disp('Press any key to continue');
y = channel_filter(x, 1, 0.2, 800, fs);
figure; eye_diagram(y, Rb, fs);
