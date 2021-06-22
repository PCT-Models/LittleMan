%% TG - Initialise - 26-11-2019
function [t0ref,t1ref,t2ref,t0ddot,t1ddot,t2ddot,t0dot,t1dot,t2dot,t0,t1,t2, ...
          pl0,pl1,pl2,pt0,pt1,pt2] = initialize()
      
%  global t0ref t1ref t2ref t0ddot t1ddot t2ddot t0dot t1dot t2dot t0 t1 t2...
%         pl0 pl1 pl2 pt0 pt1 pt2   
    
 t0ref = 0.0; t1ref = -0.3; t2ref = 0.5;    
 t0ddot = 0.0;  t0dot = 0.0;  t0 = -0.340;
 t1ddot = 0.0;  t1dot = 0.0;  t1 = -0.824;
 t2ddot = 0.0;  t2dot = 0.0;  t2 = 1.639;
 pl0 = 0.0;         pl1 = 0.0;      pl2 = 0.0;
 pt0 = 0.0063;      pt1 = -.1185;   pt2 = 0.0;
end