%% Init Dynamics - TG Footscray 01-12-2019

function [gravity,dt,dt0,pt0,pt1,pt2] = initdynam(t0ref,t1ref,t2ref)
%   global t0ref t1ref t2ref pt0 pt1 pt2 dt dt0
  pt0 = t0ref; pt1 = t1ref; pt2 = t2ref;
  gravity = 9.8; dt = 0.01; dt0 = dt/4.0;
end