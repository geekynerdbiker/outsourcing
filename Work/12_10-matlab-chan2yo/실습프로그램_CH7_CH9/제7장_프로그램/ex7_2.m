% ---------------------------------------------------------------
% ex7_2.m 
% Matlab program example for Practical Sampling
% CT signal is assumed to be sinc pulse 
% ---------------------------------------------------------------
clear; close all;
ts = 1 / 2000;         % Sampling interval(time resolution) for Experiment
fs = 1 / ts;
T1 = -10; T2 = 10;
time = T1:ts:T2;       % Time vector
df = 0.01;             % Frequency Resolution;
% -------------------------------------------------------------------------
B = 0.5;               % Signal bandwidth
x = sinc(2*B*time);    % Original signal
p_ts = 0.2;            % Sampling interval for practical sampling
p_width = 0.04;        % Pulse width
% -------------------------------------------------------------------------
pt = zeros(1, length(time));
pt(time > -p_width/2 & time <= p_width/2) = 1;
[PF, pt1, df_pt] = fft_mod(pt, ts, df);
PF = PF/fs;
PF = fftshift(abs(PF));
freq_pt = (0:df_pt:df_pt*(length(pt1)-1)) - fs/2;
% -------------------------------------------------------------------------
p_ts_index = p_ts/ts;
p_width_index = p_width/ts;
p_row = p_ts_index;
p_col = fix(length(x)/p_ts_index);
y = x(1:p_row*p_col);
% =========================================================================
% Practical Sampling #1 : Natural Sampling
% -------------------------------------------------------------------------
y_s1 = reshape(y, p_row, p_col);
y_s1( fix(p_width_index/2)+1 : end-fix(p_width_index/2), : ) = 0;
y_s1 = y_s1(:)';
y_s1 = [y_s1, zeros(1, length(x)-p_row*p_col)];
% -------------------------------------------------------------------------
% Practical Sampling #2 : Flat-top Sampling
% -------------------------------------------------------------------------
y_s2 = reshape(y, p_row, p_col);
y_s2( fix(p_width_index/2)+1 : end-fix(p_width_index/2), : ) = 0;
init_value = y_s2(end-fix(p_width_index/2)+1, : ); 
init_matrix = ones(fix(p_width_index/2), 1)*init_value;
y_s2(end-fix(p_width_index/2)+1:end, : ) = init_matrix;
y_s2(1:fix(p_width_index/2),:)=[y_s2(1:fix(p_width_index/2),1),init_matrix(:,1:end-1)];
y_s2 = y_s2(:)';
y_s2 = [y_s2, zeros(1, length(x)-p_row*p_col)];
% -------------------------------------------------------------------------
[X, x1, df_x] = fft_mod(x, ts, df);
X = X / fs;
X = fftshift(abs(X));
freq_x = (0:df_x:df_x*(length(x1)-1)) - fs/2;
% -------------------------------------------------------------------------
[Y_s1, y_s11, df_ys1] = fft_mod(y_s1, ts, df);
Y_s1 = Y_s1 * (p_ts);
Y_s1 = Y_s1 / fs;
Y_s1 = fftshift(abs(Y_s1));
freq_ys1 = (0:df_ys1:df_ys1*(length(y_s11)-1)) - fs/2;
% -------------------------------------------------------------------------
[Y_s2, y_s22, df_ys2] = fft_mod(y_s2, ts, df);
Y_s2 = Y_s2 * (p_ts);
Y_s2 = Y_s2 / fs;
Y_s2 = fftshift(abs(Y_s2));
freq_ys2 = (0:df_ys2:df_ys2*(length(y_s22)-1)) - fs/2;
% =========================================================================
AXIS_TIME1 = [-4, 4, -0.5, 1.5];
AXIS_TIME2 = [-2, 2, -0.5, 1.5];
plot(time, x); 
grid on; axis(AXIS_TIME1);
xlabel('time [sec]'); title('Original signal x(t)');
disp('hit any key to continue'); pause  
figure; plot(time, x, 'k'); hold on;
stairs(time, y_s1, 'b'); hold on;
grid on; axis(AXIS_TIME2);
xlabel('time [sec]'); title('Practical Sampling : Natural Sampling');
disp('hit any key to continue'); pause 
figure; plot(time, x, 'k'); hold on;
stairs(time, y_s2, 'b'); hold on;
grid on; axis(AXIS_TIME2);
xlabel('time [sec]'); title('Practical Sampling : Flat-top Sampling');
% -------------------------------------------------------------------------
disp('hit any key to continue'); pause 
AXIS_FREQ1 = [-5*B, 5*B, 0, 1.2];
AXIS_FREQ2 = [-40*B, 40*B, 0, 0.05];
figure; plot(freq_x, X);
grid on; axis(AXIS_FREQ1);
xlabel('frequency [Hz]'); title('Specturm of Original signal x(t)');
disp('hit any key to continue'); pause 
figure; plot(freq_pt, PF, 'k'); hold on;
stairs(freq_ys1, Y_s1, 'b'); hold on;
grid on; axis(AXIS_FREQ2);
xlabel('frequency [Hz]'); title('Specturm of Natural Sampling');
disp('hit any key to continue'); pause 
figure; plot(freq_pt, PF, 'k'); hold on;
stairs(freq_ys2, Y_s2, 'b'); hold on;
grid on; axis(AXIS_FREQ2);
xlabel('frequency [Hz]'); title('Specturm of Flat-top Sampling');