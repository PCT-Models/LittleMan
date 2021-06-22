function [o3e,o3a,o3d] = ver_az_dist(FRy,TRy,FRx,TRx,TLRd,FLRd)

global g3e g3a g3d d3e d3a d3d t0 t1 t2

r3e = 0; r3a = 0; r3d = 0;

p3e = FRy - TRy;
p3a = FRx - TRx;
p3d = TLRd - FLRd;

% e3d = r3d - p3d;
% e3e = r3e - p3e;
% e3a = r3a - p3a;
% 
% i3e = g3e * e3e;
% i3a = g3a * e3a;
% i3d = g3d * e3d;
% 
% o3e = (i3e/3) + (d3e * e3e); 
% o3a = (i3a/3) + (d3a * e3a); 
% o3d = (i3d/3) + (d3d * e3d); 

o3e = p3e; 
o3a = p3a; 
o3d = p3d; 

end