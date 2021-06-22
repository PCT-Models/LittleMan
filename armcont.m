function [t0,t1,t2,t0ref,t1ref,t2ref] = armcont(t0,t1,t2)


       
t0ref = t0/651.9;
t1ref = t1/651.9;
t2ref = t2/651.9;
 
[pt0,pt1,pt2,oldpl0,oldpl1,oldpl2] = ...
                        control(t0,t1,t2,t0ref,t1ref,t2ref,oldpl0,oldpl1,oldpl2, ...
                        pt0,pt1,pt2,t0d,t1d,t2d,loopgain0,loopgain1,loopgain2);
[t0,t1,t2] = evaluate(t0,t1,t2,t0dot,t1dot,t2dot,q1,q2,q3,g1,g2,dt0, ...
                                torque0,torque1,torque2);
          
t0 = t0 * 651.9;
t1 = t1 * 651.9;
t2 = t2 * 651.9;

end