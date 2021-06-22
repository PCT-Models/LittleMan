function [ghx,ghy,g3e,g3a,g3d,d3e,d3a,d3d,gs0,is0,gs1,is1,gs2,is2, ...
        kg0,kt0,kd0,ko0,ks0,kg1,kt1,kd1,ko1,ks1,kg2,kt2,kd2,ko2,ks2] = setparam()

% global ghx ghy g3e g3a g3d d3e d3a d3d gs0 is0 gs1 is1 gs2 is2 ...
%        kg0 kt0 kd0 ko0 ks0 kg1 kt1 kd1 ko1 ks1 kg2 kt2 kd2 ko2 ks2


ilist = [20,20,60,60,60,100,100,100];
ghx = ilist(1);ghy = ilist(2);
g3e = ilist(3);g3a = ilist(4);g3d = ilist(5);
d3e = ilist(6);d3a = ilist(7);d3d = ilist(8);
%
% Brainstem List
slist = [10,50,10,50,10,50];
gs0 = slist(1); is0 = slist(2); gs1 = slist(3); is1 = slist(4); gs2 = slist(5); is2 = slist(6);
%
% Kinesthetic List
flist = [3,1,0.01,1,300,3,1,0.01,1,200,3,1,0.005,1,50];
kg0 = flist(1); kt0 = flist(2); kd0 = flist(3); ko0 = flist(4); ks0 = flist(5); 
kg1 = flist(6); kt1 = flist(7); kd1 = flist(8); ko1 = flist(9); ks1 = flist(10);
kg2 = flist(11);kt2 = flist(12);kd2 = flist(13);ko2 = flist(14);ks2 = flist(15);


end