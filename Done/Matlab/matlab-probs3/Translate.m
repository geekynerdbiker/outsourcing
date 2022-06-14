% Translation
 
X = [0,0,0,0,0,0,0,0]';
 Y = [-0.5,0.5,0.5,1,0,-1,-0.5,-0.5]';
 Z = [0,0,0.5,0.5,1,0.5,0.5,0]';

 ARROW = [X,Y,Z,0*X+1]';
 
 c = cos(-25*pi/180);
 s = sin(-25*pi/180);
 Ry = [c,0,-s,0;0,1,0,0;s,0,c,0;0,0,0,1];
 c = cos(-45*pi/180);
 s = sin(-45*pi/180);
 Rz = [c,-s,0,0;s,c,0,0;0,0,1,0;0,0,0,1]
 Tdisp = Ry*Rz

 T = eye(4,4);
 for i=1:180
    dx = sin(i*pi/90);
    T(1,4) = dx;
    Display3D(T*ARROW, Tdisp);
    pause(0.01);
 end
 
  for i=1:180
    dy = sin(i*pi/90);
    T(2,4) = dy;
    Display3D(T*ARROW, Tdisp);
    pause(0.01);
  end
 
   for i=1:180
    dz = sin(i*pi/90);
    T(3,4) = dz;
    Display3D(T*ARROW, Tdisp);
    pause(0.01);
 end

    