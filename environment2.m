function environment2(t1,t2)
global ra1 rb1 SHx SHy ELx ELy FIx FIy
%/* t1 is angle of upper arm above horizontal. 
%   t2 is angle from extension of upper arm to forearm */
%
%/*FIND X,Y,Z COORDINATES OF ELBOW */
ELx = SHx + ra1*cosd(t1);
ELy = SHy + ra1*sind(t1);
%
%/*FIND X,Y,Z COORDINATES OF FINGERTIP */
%/* radius, shoulder-finger */ (ra1,rb1 - length of two links upper and lower)
FIx =  ELx + (rb1 * cosd(t1 + t2));
FIy =  ELy + (rb1 * sind(t1 + t2));
%

end