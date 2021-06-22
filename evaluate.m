%% TG - 26-11-2019 Evaluate
function [t0,t1,t2] = evaluate(t0,t1,t2,t0dot,t1dot,t2dot,q1,q2,q3,g1,g2,dt0,I0, ...
                                torque0,torque1,torque2)

%global t0 t1 t2 torque0 torque1 torque2 I0 q1 q2 q3 t0dot t1dot t2dot t0ddot t1ddot t2ddot g1 g2 dt0
       

co1 = cosd(t1); co2 = cosd(t2); 
si1 = sind(t1); si2 = sind(t2); 
si3 = si1*co2 + co1*si2; 
co3 = co1*co2 - si1*si2;
c1c1 = co1 * co1; c1s3 = co1 * si3; c3c1 = co3 * co1; c3c3 = co3 * co3;
s1c1 = si1 * co1; s1c3 = si1 * co3; s3c3 = si3 * co3;

%/*make coefficients*/
a0 = ( I0 + q1*c1c1 + 2.0*q2*c3c1 + q3*c3c3 ); %/*t0ddot*/
b0 = -2.0 * t0dot * (...
              (q1*s1c1 + q2*s1c3 + q3*s3c3)* t1dot...
             +(q2*c1s3 + q3*s3c3) * t2dot);


a1 = q1 + 2.0*q2*co2 + q3;
b1 = q2*co2 + q3;
c1 =  (q1*s1c1 + q2*(s1c3-c1s3) + q3*s3c3) * t0dot * t0dot...
      -q2*si2*t2dot*(t2dot + 2.0 * t1dot)...
      + g1*co1 + g2*co3;

a2 = b1;
b2 = q3;
c2 =   (q2*c1s3 + q3*s3c3) * t0dot*t0dot...
        + q2 * si2 * t1dot * t1dot...
        + g2*co3;

denom = (a1*b2 - a2*b1);

t0ddot = (torque0 - b0) / a0;
t0dot  = t0dot + t0ddot * dt0;
t0     = t0 + t0dot * dt0 + 0.5*t0ddot*dt0*dt0;

t1ddot = ( (b2*torque1 - b1*torque2) - (b2*c1 - b1*c2) ) / denom;
t1dot = t1dot + t1ddot * dt0;
t1 =  t1 + t1dot* dt0 + 0.5*t1ddot*dt0*dt0;

t2ddot = ( (a1*torque2 - a2*torque1) - (a1*c2 - a2*c1) ) / denom;
t2dot = t2dot + t2ddot * dt0;
t2 = t2 + t2dot * dt0 + 0.5*t2ddot*dt0*dt0;

    if(t2 < 0.0)
       t2 = 0.0;
    end
end