%% TG - Makeconstants 26-11-2019

function [q1,q2,q3,g1,g2,loopgain0,loopgain1,loopgain2,ra1,rb1,I0] = makeconstants(kt0,kt1,kt2,ko0, ...
                                                                  ko1,ko2,ks0,ks1,ks2)

% global kt0 kt1 kt2 ko0 ko1 ko2 ks0 ks1 ks2 q1 q2 q3 g1 g2 loopgain0 loopgain1 loopgain2 I0 ra1 rb1

gravity = 1;
% base1 = 2 * vsize/14;
% base2 = 4 * vsize/14;
% base3 = 6 * vsize/14;
% base4 = 8 * vsize/14;
% base5 = 10 *vsize/14 ;
% base6 = 12*vsize/14;

%/* everything in MKS units, from measurements of my arm */
m1 = 2.73;  m2 = 1.25; %/* -- masses, kg */
I0 = 1.0;
% l1 = 0.36; l2 = 0.33; %/*-- link lengths*/
l1 = 1.0; l2 = 1.0;
l1c = l1/2.0; l2c = l2/2.0;
I1 = 0.6404; I2 = 0.084; %/* moments of inertia from measured geometry */
q1 = m1*l1c*l1c + I1 + m2*l1*l1;
q2 = m2*l1*l2c;
q3 = m2*l2c*l2c + I2;
if (gravity == 1) 
    gg = 9.8;
else
    gg = 0.0;
end
ra1 = l1; rb1 = l2;
g1 = (m1*l1c + m2*l1) * gg;
g2 = m2*l2c*gg;
loopgain0 = kt0*ko0*ks0;
loopgain1 = kt1*ko1*ks1;
loopgain2 = kt2*ko2*ks2;
end