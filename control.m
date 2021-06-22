function [pt0,pt1,pt2,oldpl0,oldpl1,oldpl2,torque0,torque1,torque2] = ...
                        control(t0,t1,t2,t0ref,t1ref,t2ref,oldpl0,oldpl1,oldpl2, ...
                        pt0,pt1,pt2,t0d,t1d,t2d,kg0,kg1,kg2,ko0,ks0,ko1,ks1,ko2,ks2, ...
                        kd0,kd1,kd2,kt0,kt1,kt2,dt0,loopgain0,loopgain1,loopgain2)

 pl0 = kg0 * (t0ref - t0);
 pl1 = kg1 * (t1ref - t1);
 pl2 = kg2 * (t2ref - t2);
 
 t00d = t0d + 0.7*((pl0 - oldpl0)/dt0 - t0d);
 t11d = t1d + 0.7*((pl1 - oldpl1)/dt0 - t1d);
 t22d = t2d + 0.7*((pl2 - oldpl2)/dt0 - t2d);

 oldpl0 = pl0; oldpl1 = pl1; oldpl2 = pl2;

 e0 = t0ref + pl0 - pt0 + kd0*t00d; %/* damping added here */
 e1 = t1ref + pl1 - pt1 + kd1*t11d; %/* to allow computing current value */
 e2 = t2ref + pl2 - pt2 + kd2*t22d;

 torque0 = -ks0 * (t0 - ko0*e0);
 torque2 = -ks2 * (t2 - ko2*e2);
 torque1 = -ks1 * (t1 - ko1*e1) - torque2/2;
 
 pt0 = pt0 + (torque0*kt0 - pt0)/ (1.0 + loopgain0)/5.0 ; %/* azimuth*/
 pt1 = pt1 + (torque1*kt1 - pt1)/ (1.0 + loopgain1)/5.0 ; %/* elevation */
 pt2 = pt2 + (torque2*kt2 - pt2)/ (1.0 + loopgain2)/5.0 ; %/* distance */
end