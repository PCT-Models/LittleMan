function [Ax,Ay] = rotateimage(x,y,z,th2,ph2)

yp =  y * cosd(th2) + z * sind(th2);
zp =  -y * sind(th2) + z * cosd(th2);

y = yp; z = zp;

xp =  x * cosd(ph2) + z * sind(ph2);
zp =  -x * sind(ph2) + z * cosd(ph2);

x = xp; z = zp;


Ax = findangle(z,x);
Ay = findangle(z,y);


end