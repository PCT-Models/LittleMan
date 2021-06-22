function [o2a,o2e,o2d] = link3to2(o3a,o3e,o3d)

global gs0 gs1 gs2 t1 t2 t0

r2e = o3e;     
r2a = o3a;
r2d = o3d;
% r2d = 2048 - r2d;   %/* convert output for external-angle control */

p2e = t1 + 0.5*t2;      %/* ELEVATION PERCEPTION */
p2a = t0;               %/* AZIMUTH PERCEPTION */
p2d = t2;               %/* DISTANCE PERCEPTION */

e2e = r2e - p2e;
e2a = r2a - p2a;
e2d = r2d - p2d;    %/* error is eternal elbow angle error */

oa = e2a * gs0; %           /* azimuth      */
oe = e2e * gs1; %           /* elevation    */
od = e2d * gs2; %           /* distance     */

o2a = oa;
o2d = od;
o2e = oe - 0.5*o2d;         %/* prevent reach from disturbing elevation */

end