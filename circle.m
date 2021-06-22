function [xunit,yunit] = circle(x,y,r)

th = pi/2:pi/50:pi;
xunit = r * cos(th) + x;
yunit = r * sin(th) + y;

end