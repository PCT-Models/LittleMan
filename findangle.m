function theta = findangle(x,y)

u = abs(x); v = abs(y);
% if( v <= u) 
    theta = atand(v/u);
% else
%     theta = 90 - atan(u/v);
% end
% if( x < 0) 
%     theta = 180 - theta;
% end
% if( y < 0) 
%     theta = - theta;
% end
 
 end