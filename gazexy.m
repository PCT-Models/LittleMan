function [o2dr,o2dl,o1e] = gazexy(TRx,TLx,TRy)
global ghx ghy i2dl i2dr i1e
r2dr = 0;
r2dl = 0;
 
p2dr = TRx;         %/* perceived x target deviation from gaze angle */
p2dl = TLx;
 
e2dr = r2dr - p2dr;
e2dl = r2dl - p2dl;
i2dl = i2dl - e2dl;        %/* integral of error signal */
i2dr = i2dr - e2dr;
o2dr = i2dr * ghx;  %/* head angle, x */
o2dl = i2dl * ghx;

r1e = 0;
p1e = TRy;         %/* perceived y target deviation from gaze angle */
e1e = r1e - p1e;
i1e = i1e - e1e;       %/* integral of error signal */
o1e = i1e * ghy; %/* head angle, y */          
end
