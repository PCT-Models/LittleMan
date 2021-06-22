function [a,e,r] = link2to1()

[a,e,r,t0ref,t1ref,t2ref] = armcont(t0,t1,t2);

% /* HEAD-EYE CONTROL SYSTEMS, NO KINESTHETIC LEVEL */
 gazexle = o2dl;   %/* gaze x, left eye */
 gazexre = o2dr;   %/* gaze x, right eye */
 gazex = (gazexle + gazexre)/2;
 gazey = o1e;      %/* gaze y, head direction */


end