function armdynam()

global hsize vsize hcenter vcenter interval time testnum test1 usediagram r2e p2e o2e ...
	   r2a p2a o2a r2d p2d o2d;

numkparams = 15;
numvparams = 8;
t0d = 0.0; t1d = 3.0e-6; t2d = -5.0e-6;
    
% void armcont(int *a, int *e, int *f, int aref,int eref,int fref);
% void initdynam(void);
% void setgravity(void);
% void makeconstants(void);
% void evaluate(float torque0,float torque1,float torque2);
% void initialize(void);
% void control(void);
% void showangles(int a1,int a2,int a3);
% void showfloat(char *s, int x, int y, float n);
% void showcontrol(int level, int which);

function showfloat(s,x,y,n)
char nstr[200];
sprintf(nstr,"%15s %8.3f",s,n);
setfillstyle(0,0);
bar(x,y,x+textwidth(nstr),y+textheight("1"));
outtextxy(x,y,nstr);
end

function makeconstants()
base1 = 2 * vsize/14;
base2 = 4 * vsize/14;
base3 = 6 * vsize/14;
base4 = 8 * vsize/14;
base5 = 10 *vsize/14 ;
base6 = 12*vsize/14;

% everything in MKS units, from measurements of my arm
m1 = 2.73;  m2 = 1.25; % -- masses, kg
I0 = 1.0;
l1 = 0.36; l2 = 0.33; %-- link lengths*/
l1c = l1/2.0; l2c = l2/2.0;
I1 = 0.6404; I2 = 0.084; % moments of inertia from measured geometry */
q1 = m1*l1c*l1c + I1 + m2*l1*l1;
q2 = m2*l1*l2c;
q3 = m2*l2c*l2c + I2;
if (gravity) == 1
    gg = 9.8;
else
     gg = 0.0;
end     
g1 = (m1*l1c + m2*l1) * gg;
g2 = m2*l2c*gg;
loopgain0 = kt0*ko0*ks0;
loopgain1 = kt1*ko1*ks1;
loopgain2 = kt2*ko2*ks2;
end

function evaluate(torque0,torque1,torque2)
        
        co1 = cos(t1);
        co2 = cos(t2);
        si1 = sin(t1);
        si2 = sin(t2);
        si3 = si1*co2 + co1*si2;
        co3 = co1*co2 - si1*si2;
        c1c1 = co1 * co1;
        c1s3 = co1 * si3;
        c3c1 = co3 * co1;
        c3c3 = co3 * co3;
        s1c1 = si1 * co1;
        s1c3 = si1 * co3;
        s3c3 = si3 * co3;
        
        %make coefficients*/
        
        a0 = ( I0 + q1*c1c1 + 2.0*q2*c3c1 + q3*c3c3 ); %t0ddot*/
        b0 = -2.0 * t0dot * ( ...
            (q1*s1c1 + q2*s1c3 + q3*s3c3) * t1dot ...
            +(q2*c1s3 + q3*s3c3) * t2dot ...
            );
        
        
        a1 = q1 + 2.0*q2*co2 + q3;
        b1 = q2*co2 + q3;
        c1 =  (q1*s1c1 + q2*(s1c3-c1s3) + q3*s3c3) * t0dot * t0dot ...
            -q2*si2*t2dot*(t2dot + 2.0 * t1dot)...
            + g1*co1 + g2*co3;
        a2 = b1;
        b2 = q3;
        c2 =   (q2*c1s3 + q3*s3c3) * t0dot*t0dot ...
            + q2 * si2 * t1dot * t1dot ...
            + g2*co3;
        
        denom   = (a1*b2 - a2*b1);
        t0ddot  = (torque0 - b0) / a0;
        t0dot   = t0dot + (t0ddot * dt0);
        t0      = t0 + t0dot * dt0 + 0.5*t0ddot*dt0*dt0;
        
        t1ddot  = ( (b2*torque1 - b1*torque2) - (b2*c1 - b1*c2) ) / denom;
        t1dot   = t1dot + t1ddot * dt0;
        t1      = t1 + t1dot* dt0 + 0.5*t1ddot*dt0*dt0;
        
        t2ddot  = ( (a1*torque2 - a2*torque1) - (a1*c2 - a2*c1) ) / denom;
        t2dot   = t2dot + t2ddot * dt0;
        t2      = t2 + t2dot * dt0 + 0.5*t2ddot*dt0*dt0;
        if(t2 < 0.0)
            t2 = 0.0;
        end
end

function initialize()
t0ref = 0.0; t1ref = -0.3; t2ref = 0.5;
t0ddot = 0.0;  t0dot = 0.0;  t0 = -0.340;
t1ddot = 0.0;  t1dot = 0.0;  t1 = -0.824;
t2ddot = 0.0;  t2dot = 0.0;  t2 = 1.639;
pl0 = 0.0;    pl1 = 0.0; pl2 = 0.0;
pt0 = 0.0063;    pt1 = -.1185; pt2 = 0.0;
end

function initdynam()
  initialize(); makeconstants();
  initialized = !1;
  pt0 = t0ref; pt1 = t1ref; pt2 = t2ref;
  gravity = 0; dt = 0.01; dt0 = dt/4.0;
end

function setgravity()
 gravity = !gravity;
 makeconstants();
end

function showangles(a1,a2,a3)
    t = 0;
    old0,old1,old2;
    if(test1)
        s0=s1=s2=testnum;
    else
        s0 = 0; s1 = 1; s2 = 2;
        mark = (t+1) % interval;
    end
    if(mark == 0)
        for i=-2:1:3
            if(s0 == 0) putpixel(t,base1 - a1/2 + i,WHITE);end
            if(s1 == 1) putpixel(t,base2 - a2/2 + i,WHITE);end
            if(s2 == 2) putpixel(t,base3 - a3/2 + i,WHITE);end
            if(s0 == 0) putpixel(t,base4 - torque0/4.0 + i,WHITE);end
            if(s1 == 1) putpixel(t,base5 - torque1/4.0 + i,WHITE);end
            if(s2 == 2) putpixel(t,base6 - 3.0*torque2 + i,WHITE);end
        end
        if(s0 == 0) putpixel(t,base1 - a1/2,WHITE);end
        if(s1 == 1) putpixel(t,base2 - a2/2,WHITE);end
        if(s2 == 2) putpixel(t,base3 - a3/2,WHITE);end

        setwritemode(0);
        moveto(t-1,old0);
        old0 = base4 - torque0/4.0;
        if(s0 == 0) lineto(t,old0);end

        moveto(t-1,old1);
        old1 = base5 - torque1/4.0;
        if(s1 == 1) lineto(t,old1);end

        moveto(t-1,old2);
        old2 = base6 - 3.0*torque2;
        if(s2 == 2) lineto(t,old2);end
        setwritemode(1);

        t = t+1;

        if((t / (20*interval)) == 0)
            t = 0; time = 0;
            setviewport(0,0,200,vsize - 1,0);
            clearviewport();
            setviewport(0,0,hsize-1, vsize-1,0);
            outtextxy(0,1,"ANGLES:");
            if(s0 == 0) outtextxy(0,base1 - a1/2 - 12,"Sh. X");end
            if(s1 == 1) outtextxy(0,base2 - a2/2 - 12,"Sh. Y");end
            if(s2 == 2) outtextxy(0,base3 - a3/2 - 12,"Elbow");end
            outtextxy(0,vcenter,"TORQUES:");
            if(s0 == 0) outtextxy(0,base4 - torque0/5 - 12,"Sh. X");end
            if(s1 == 1) outtextxy(0,base5 - torque1/5 - 12,"Sh. Y");end
            if(s2 == 2) outtextxy(0,base6 - torque2/5 - 12,"Elbow");end
        end
    end
end

function showcontrol(level,which)   % using lineto for plots */
    t = 0; oldt = 0; oldaccel; oldvel; oldangle; timescale;
    i;accel;vel;x;angle;hscale;

    if (t == 0) oldt = 0;end
    if (level == 2) timescale = 0.5; else timescale = 2.0; end
    if(level == 1)
        switch (which)
            case 0: accel = t0ddot/4.0;
                vel = 5.0*t0dot;
                angle = 100*t0 - 50;
                break;
            case 1:  accel = t1ddot/4.0;
                vel = 5.0*t1dot;
                angle = 100*t1 - 50;
                break;
            case 2:  accel = t2ddot/4.0;
                vel = 5.0*t2dot;
                angle = 100*t2 - 50;
                break;
        end
    else
        switch (which)
            case 1: accel = r2e/10.0;
                vel = p2e/10;
                angle = o2e/10 + 30;
                break;
            case 0:  accel = r2a/10;
                vel = p2a/10;
                angle = o2a/10;
                break;
            case 2:  accel = r2d/10 - 100;
                vel = p2d/10 - 100;
                angle = o2d/10 - 150;
                break;
        end
        x = timescale * t * dt/0.01;
        if(t==1) oldt = 0;end
        if(t == 0) oldaccel = accel;end
        moveto(oldt,vsize/4 - oldaccel);
        lineto(x,vsize/4 - accel);
        if(t == 0) oldvel = vel;end
        moveto(oldt,2*vsize/4 - oldvel);
        lineto(x,2 * vsize/4 - vel);
        if(t == 0) oldangle = angle;end
        moveto(oldt,3*vsize/4 - oldangle);
        lineto(x,3 * vsize/4 - angle);
        oldt = x;
        oldaccel = accel; oldvel = vel; oldangle = angle;

        mark = (t) % interval;
        if(mark == 0)
            for i=-2:1:3
                putpixel(timescale * t,    vsize/4 - accel+ i,WHITE);
                putpixel(timescale * t,2 * vsize/4 - vel+ i,WHITE);
                putpixel(timescale * t,3 * vsize/4 - angle + i,WHITE);
            end
        end
        hscale = 20*interval/timescale;
        if((t / hscale) == 0)
            t = 0; time = 0;
            setviewport(0,0,200,vsize - 1,0);
            clearviewport();
            setviewport(0,0,hsize-1, vsize-1,0);
            if(level == 1)
                switch(which)
                    case 1: outtextxy(hcenter/4,0,"SHOULDER Y"); break;
                    case 0: outtextxy(hcenter/4,0,"SHOULDER X"); break;
                    case 2: outtextxy(hcenter/4,0,"ELBOW"); break;
                end
                outtextxy(50,1*vsize/4-20,"ACCEL");
                outtextxy(50,2*vsize/4-20,"VEL");
                outtextxy(50,3*vsize/4-20,"ANGLE");
            else
                switch(which)
                    case 1: outtextxy(hcenter/4,0,"ELEVATION"); break;
                    case 0: outtextxy(hcenter/4,0,"AZIMUTH"); break;
                    case 2: outtextxy(hcenter/4,0,"RADIUS"); break;
                end
                outtextxy(0,1*vsize/4-60,"REF SIG");
                outtextxy(0,2*vsize/4-45,"PERCEP");
                outtextxy(0,3*vsize/4-20,"OUTPUT");
            end
        end
        t = t+1;
    end
end

function control()
oldpl0 = 0.0; oldpl1 = 0.0; oldpl2 = 0.0;

 pt0 = pt0 + (torque0*kt0 - pt0)/ (1.0 + loopgain0)/5.0 ; /* azimuth*/
 pt1 = pt1 + (torque1*kt1 - pt1)/ (1.0 + loopgain1)/5.0 ; /* elevation */
 pt2 = pt2 + (torque2*kt2 - pt2)/ (1.0 + loopgain2)/5.0 ; /* distance */

 pl0 = kg0 * (t0ref - t0);
 pl1 = kg1 * (t1ref - t1);
 pl2 = kg2 * (t2ref - t2);

 t0d = t0d + 0.7*((pl0 - oldpl0)/dt0 - t0d);
 t1d = t1d + 0.7*((pl1 - oldpl1)/dt0 - t1d);
 t2d = t2d + 0.7*((pl2 - oldpl2)/dt0 - t2d);

 oldpl0 = pl0; oldpl1 = pl1; oldpl2 = pl2;

 e0 = t0ref + pl0 - pt0 + kd0*t0d; % damping added here */
 e1 = t1ref + pl1 - pt1 + kd1*t1d; % to allow computing current value */
 e2 = t2ref + pl2 - pt2 + kd2*t2d;

 torque0 = -ks0 * (t0 - ko0*e0);
 torque2 = -ks2 * (t2 - ko2*e2);
 torque1 = -ks1 * (t1 - ko1*e1) - torque2/2;

end

function armcont(a,e,r,azimuth,elevation,reach)
t0ref = azimuth/651.9;
t1ref = elevation/651.9;
t2ref = reach/651.9;
control();
evaluate(torque0,torque1,torque2);
evaluate(torque0,torque1,torque2);
evaluate(torque0,torque1,torque2);
evaluate(torque0,torque1,torque2);
evaluate(torque0,torque1,torque2);
a = t0 * 651.9;
e = t1 * 651.9;
r = t2 * 651.9;
end

end

