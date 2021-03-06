%% Text representation - TG Footscray, Melbourne 25-11-2019
close all; clc; clear;

vsize = 500; hsize = 1000; vcenter = vsize/2; hcenter = hsize/2;
figure('Renderer', 'painters', 'Position', [10 10 hsize vsize]);
axis([0 1000 0 vsize]);
vn = 20; hn = 10;
% %% Powers Display
% text(4*hn,vsize-(1*vn),'TAx');
% text(4*hn,vsize-(2*vn),'TAy');
% text(4*hn,vsize-(3*vn),'TAz');
% text(16*hn,vsize-(1*vn),'FIx');
% text(16*hn,vsize-(2*vn),'FIy');
% text(16*hn,vsize-(3*vn),'FIz');
% %  gotoxy(4,1); cprintf("%5d",TAx);
% %  gotoxy(4,2); cprintf("%5d",TAy);
% %  gotoxy(4,3); cprintf("%5d",TAz);
% %  gotoxy(16,1); cprintf("%5d",FIx);
% %  gotoxy(16,2); cprintf("%5d",FIy);
% %  gotoxy(16,3); cprintf("%5d",FIz);
% %
% text(32*hn,vsize-(5*vn),'r3a');
% text(22*hn,vsize-(8*vn),'p3a');
% text(28*hn,vsize-(8*vn),'e3a');
% text(34*hn,vsize-(8*vn),'o3a');
% %  gotoxy(32,5); cprintf("%4d",r3a);
% %  gotoxy(22,8); cprintf("%5d",p3a);
% %  gotoxy(28,8); cprintf("%5d",e3a);
% %  gotoxy(34,8); cprintf("%5d",o3a);
% %
% text(42*hn,vsize-(4*vn),'p3d');
% text(48*hn,vsize-(4*vn),'e3d');
% text(54*hn,vsize-(4*vn),'o3d');
% %  gotoxy(42,4); cprintf("%5d",p3d);
% %  gotoxy(48,4); cprintf("%5d",e3d);
% %  gotoxy(54,4); cprintf("%5d",o3d);
% % 
% text(72*hn,vsize-(5*vn),'r3e');
% text(62*hn,vsize-(8*vn),'p3e');
% text(68*hn,vsize-(8*vn),'e3e');
% text(74*hn,vsize-(8*vn),'o3e');
% %  gotoxy(72,5); cprintf("%4d",r3e);
% %  gotoxy(62,8); cprintf("%5d",p3e);
% %  gotoxy(68,8); cprintf("%5d",e3e);
% %  gotoxy(74,8); cprintf("%5d",o3e);
% %
% text(22*hn,vsize-(21*vn),'az');
% text(28*hn,vsize-(21*vn),'e2a');
% text(34*hn,vsize-(21*vn),'torque0');
% text(42*hn,vsize-(21*vn),'t2');
% %  gotoxy(22,21); cprintf("%5d",az);
% %  gotoxy(28,21); cprintf("%5d",e2a);
% %  gotoxy(34,21); cprintf("%5.1f",torque0);
% %  gotoxy(42,21); cprintf("%5d",t2);
% text(48*hn,vsize-(21*vn),'e2d');
% text(54*hn,vsize-(21*vn),'torque2');
% text(62*hn,vsize-(21*vn),'t1');
% text(68*hn,vsize-(21*vn),'e2e');
% %  gotoxy(48,21); cprintf("%5d",e2d);
% %  gotoxy(54,21); cprintf("%5.1f",torque2);
% %  gotoxy(62,21); cprintf("%5d",t1);
% %  gotoxy(68,21); cprintf("%5d",e2e);
% text(74*hn,vsize-(21*vn),'torque1');
% text(2*hn,vsize-(18*vn),'p1e');
% text(8*hn,vsize-(18*vn),'e1e');
% text(14*hn,vsize-(18*vn),'o1e');
% %  gotoxy(74,21); cprintf("%5.1f",torque1);
% %  gotoxy( 2,18); cprintf("%5d",p1e);
% %  gotoxy( 8,18); cprintf("%5d",e1e);
% %  gotoxy(14,18); cprintf("%5d",o1e);
% text(2*hn,vsize-(12*vn),'p2dl+p2dr');
% text(2*hn,vsize-(14*vn),'e2dl+e2dr');
% text(2*hn,vsize-(16*vn),'o2dl+o2dr');
% %  gotoxy( 2,12); cprintf("%5d",(p2dl+p2dr)/2);
% %  gotoxy( 8,12); cprintf("%5d",(e2dl+e2dr)/2);
% %  gotoxy(14,12); cprintf("%5d",(o2dl+o2dr)/2);
% text(30*hn,vsize-(17*vn),'r2a');
% text(50*hn,vsize-(17*vn),'r2d');
% text(70*hn,vsize-(17*vn),'r2e');
% %  gotoxy(30,17); cprintf("%5d",r2a);
% %  gotoxy(50,17); cprintf("%5d",r2d);
% %  gotoxy(70,17); cprintf("%5d",r2e);
% %
%% My Display
text(4*hn,vsize-(1*vn),'TAx');
text(4*hn,vsize-(2*vn),'TAy');
text(4*hn,vsize-(3*vn),'TAz');
text(16*hn,vsize-(1*vn),'FIx');
text(16*hn,vsize-(2*vn),'FIy');
text(16*hn,vsize-(3*vn),'FIz');
%  gotoxy(4,1); cprintf("%5d",TAx);
%  gotoxy(4,2); cprintf("%5d",TAy);
%  gotoxy(4,3); cprintf("%5d",TAz);
%  gotoxy(16,1); cprintf("%5d",FIx);
%  gotoxy(16,2); cprintf("%5d",FIy);
%  gotoxy(16,3); cprintf("%5d",FIz);
%
text(32*hn,vsize-(5*vn),'r3a');
text(22*hn,vsize-(8*vn),'p3a');
text(28*hn,vsize-(8*vn),'e3a');
text(34*hn,vsize-(8*vn),'o3a');
%  gotoxy(32,5); cprintf("%4d",r3a);
%  gotoxy(22,8); cprintf("%5d",p3a);
%  gotoxy(28,8); cprintf("%5d",e3a);
%  gotoxy(34,8); cprintf("%5d",o3a);
%
text(42*hn,vsize-(4*vn),'p3d');
text(48*hn,vsize-(4*vn),'e3d');
text(54*hn,vsize-(4*vn),'o3d');
%  gotoxy(42,4); cprintf("%5d",p3d);
%  gotoxy(48,4); cprintf("%5d",e3d);
%  gotoxy(54,4); cprintf("%5d",o3d);
% 
text(72*hn,vsize-(5*vn),'r3e');
text(62*hn,vsize-(8*vn),'p3e');
text(68*hn,vsize-(8*vn),'e3e');
text(74*hn,vsize-(8*vn),'o3e');
%  gotoxy(72,5); cprintf("%4d",r3e);
%  gotoxy(62,8); cprintf("%5d",p3e);
%  gotoxy(68,8); cprintf("%5d",e3e);
%  gotoxy(74,8); cprintf("%5d",o3e);
%
text(22*hn,vsize-(15*vn),'az');
text(28*hn,vsize-(15*vn),'e2a');
text(34*hn,vsize-(15*vn),'torque0');
text(42*hn,vsize-(15*vn),'t2');
% Insertion
text(22*hn,vsize-(18*vn),'p2a');
text(35*hn,vsize-(18*vn),'o2a');
text(44*hn,vsize-(18*vn),'p2d');
text(54*hn,vsize-(18*vn),'o2d');
text(65*hn,vsize-(18*vn),'p2e');
text(75*hn,vsize-(18*vn),'o2e');
%  gotoxy(22,21); cprintf("%5d",az);
%  gotoxy(28,21); cprintf("%5d",e2a);
%  gotoxy(34,21); cprintf("%5.1f",torque0);
%  gotoxy(42,21); cprintf("%5d",t2);
text(48*hn,vsize-(15*vn),'e2d');
text(54*hn,vsize-(15*vn),'torque2');
text(62*hn,vsize-(15*vn),'t1');
text(68*hn,vsize-(15*vn),'e2e');
%  gotoxy(48,21); cprintf("%5d",e2d);
%  gotoxy(54,21); cprintf("%5.1f",torque2);
%  gotoxy(62,21); cprintf("%5d",t1);
%  gotoxy(68,21); cprintf("%5d",e2e);
text(74*hn,vsize-(15*vn),'torque1');
text(2*hn,vsize-(11*vn),'p1e');
text(8*hn,vsize-(11*vn),'e1e');
text(14*hn,vsize-(11*vn),'o1e');
%  gotoxy(74,21); cprintf("%5.1f",torque1);
%  gotoxy( 2,18); cprintf("%5d",p1e);
%  gotoxy( 8,18); cprintf("%5d",e1e);
%  gotoxy(14,18); cprintf("%5d",o1e);
text(2*hn,vsize-(12*vn),'p2dl+p2dr');
text(2*hn,vsize-(14*vn),'e2dl+e2dr');
text(2*hn,vsize-(16*vn),'o2dl+o2dr');
%  gotoxy( 2,12); cprintf("%5d",(p2dl+p2dr)/2);
%  gotoxy( 8,12); cprintf("%5d",(e2dl+e2dr)/2);
%  gotoxy(14,12); cprintf("%5d",(o2dl+o2dr)/2);
text(30*hn,vsize-(11*vn),'r2a');
text(50*hn,vsize-(11*vn),'r2d');
text(70*hn,vsize-(11*vn),'r2e');
%  gotoxy(30,17); cprintf("%5d",r2a);
%  gotoxy(50,17); cprintf("%5d",r2d);
%  gotoxy(70,17); cprintf("%5d",r2e);
