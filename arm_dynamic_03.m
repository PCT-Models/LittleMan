%% Program Without Functions - TG Footscray 26-11-2019
clear; close all; clc;
%
% Save Elbow and Finger Coordinates (k is iteration for cell)
k = 0; elbow = {}; finger = {}; gg = 0;
%
% Display a Little Man (ArmInit)
[MEx,MEy,MEz,SHx,SHy,SHz] = body();

% Main Program 
%Setting following to zeros
e3e=0;e3a=0;e3d=0;r3e=0;r3a=0;r3d=0;
o3e = 0; o3a = 0; o3d = 0; i3e = 0; i3a = 0; i3d = 0;
oldpl0 = 0; oldpl1 = 0; oldpl2 = 0;
t0d = 0; t1d = 0; t2d = 0;
% Set Params
[ghx,ghy,g3e,g3a,g3d,d3e,d3a,d3d,gs0,is0,gs1,is1,gs2,is2, ...
        kg0,kt0,kd0,ko0,ks0,kg1,kt1,kd1,ko1,ks1,kg2,kt2,kd2,ko2,ks2] = setparam();
% Initialise
[t0ref,t1ref,t2ref,t0ddot,t1ddot,t2ddot,t0dot,t1dot,t2dot,t0,t1,t2, ...
                                pl0,pl1,pl2,pt0,pt1,pt2] = initialize();
% Make Constants
[q1,q2,q3,g1,g2,loopgain0,loopgain1,loopgain2,ra1,rb1,I0] = makeconstants(kt0,kt1,kt2,ko0, ...
                                                                  ko1,ko2,ks0,ks1,ks2);                            
% InitDynam
[gravity,dt,dt0,pt0,pt1,pt2] = initdynam(t0ref,t1ref,t2ref);

%
% Target
hold on;
TAx = 0.5; TAy = 1.0; TAz = 0.1;
plot3(TAx,TAy,TAz,'Dk','LineWidth',1.5);
xlabel('x');ylabel('y');zlabel('z');

% Arm Control;
t0ref = t0/651.9;
t1ref = t1/651.9;
t2ref = t2/651.9;
 
[pt0,pt1,pt2,oldpl0,oldpl1,oldpl2,torque0,torque1,torque2] = ...
                        control(t0,t1,t2,t0ref,t1ref,t2ref,oldpl0,oldpl1,oldpl2, ...
                        pt0,pt1,pt2,t0d,t1d,t2d,kg0,kg1,kg2,ko0,ks0,ko1,ks1,ko2,ks2, ...
                        kd0,kd1,kd2,kt0,kt1,kt2,dt0,loopgain0,loopgain1,loopgain2);
[t0,t1,t2] = evaluate(t0,t1,t2,t0dot,t1dot,t2dot,q1,q2,q3,g1,g2,dt0,I0, ...
                                torque0,torque1,torque2);
          
t0 = t0 * 651.9;
t1 = t1 * 651.9;
t2 = t2 * 651.9;
                    
% ELz = 0; FIz = 0; 
%
% Fingers and Elbow Coordinates
% environment2(az,t1,t2);t2 = elevation , t1 = elbow
% Azimuth            t0 - moves from 0 ---  180
% Shoulder Vertical  t1 - moves from 0 ---  180
% Elbow              t2 - moves from 0 ---  180
%
% Initial Position
t0 = -90;t1 = 130; t2 = 0;
for t2 = 1:1:10
[FIx,FIy,FIz,ELx,ELy,ELz] = environment(t0,t1,t2,SHx,SHy,SHz,ra1,rb1);
plot3([SHx,ELx,FIx],[SHy,ELy,FIy],[SHz,ELz,FIz],'-ok','LineWidth',1.5);  
k = k+1;
elbow{k} = [ELx,ELy,ELz];
finger{k} = [FIx,FIy,FIz];
disp(t0);disp(t1);disp(t2);
end        
   
    
view(108,4);
grid on;
axis equal;


%% Plot Elbow Positions
XY = cell2mat(elbow);
    X = XY(1:3:end);
    Y = XY(2:3:end);
    Z = XY(3:3:end);
     
%% Velocity of the Finger
XY = cell2mat(finger);
    X = XY(1:4:end);
    Y = XY(2:4:end);
    Z = XY(3:4:end);
    time = XY(4:4:end);
