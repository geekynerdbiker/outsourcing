function Display3D(DATA, T)
% scaling factor
 s = T(4,4);

% draw the X, Y, Z axis
 X = [1,0,0,1]';
 Y = [0,1,0,1]';
 Z = [0,0,1,1]';
 O = [0,0,0,1]';

 DATA = T*DATA;

 T0 = T;
 T0(1,4) = 0;
 T0(2,4) = 0;
 T0(3,4) = 0;

% transform
 X0 = T0*X;
 Y0 = T0*Y;
 Z0 = T0*Z;
 Origin = T0*O;

% display is the y-z plane
 hold off;
 plot([-2,2],[-2,2],'wx');
 hold on;

% Project onto the YZ axis

 Tx = s*[0,1,0,0];
 Ty = s*[0,0,1,0];

 plot(Tx*[Origin, X0], Ty*[Origin,X0], 'g');
 plot(Tx*[Origin, Y0], Ty*[Origin,Y0], 'r');
 plot(Tx*[Origin, Z0], Ty*[Origin,Z0], 'm');


% display the data
 plot(Tx*DATA,Ty*DATA, 'b')

end