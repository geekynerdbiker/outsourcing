function eye_diagram(x, Rb, fs)
%--------------------------------------------------------------------------
% This routine displays the Eye Diagram of x
% Rb: data rate
% fs: sampling frequency
%--------------------------------------------------------------------------
Tb = 1/Rb;
ts = 1/fs;

num_eye = 2;            % Number of eye diagrams
num_sample = Tb/ts;     % Number of samples per bit duration
L = num_eye*num_sample; % Number of samples per diagram
N = length(x); 
num_block = fix(N/L); 
if(num_block > 100) 
    num_block = 100;
end

index = [1:(num_eye*num_sample)];
index = index + L; % skip initial data
num_block = num_block - 1;
%
time_vec = ts * [0:L]; % Time for displaying the diagram
max_input = max(abs(x));
% -----------------------------------------------------------------------
delta = x(2) - x(1);
x0 = x(1) - delta;    % Estimate the first data of the input
if(((x0 < 0) & (x(1)>0)) | ((x0>0) & (x(1)<0))) x0 = 0; end
y = x(index);
plot(time_vec,[x0 y(:).'],'b');  grid on;
xlabel('Time [sec]'); title('Eye Diagram');
hold on
last = max(index);

z = zeros(L, num_block-1);
z(:) = x( L+1 : num_block*L );
front = z(L,:);
front = [x(last) front(1:num_block-2)];
z = [front;  z];

plot(time_vec, z,'b');

%axis([0 max(time_vec) -1.25*max_input 1.25*max_input]), ...
axis([0 max(time_vec) -2  2]), ...
hold off
