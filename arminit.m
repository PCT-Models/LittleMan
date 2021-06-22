function [headheight,headwidth,eyesize,neck,ra1,rb1,REx,REy,REz,LEx,LEy,LEz,SHx,SHy,SHz,...
          FIx,FIy,FIz,i3a,i3e,i3d] = arminit(vsize,TAx,TAy,TAz)
 halfside = vsize / 2;
 headheight = halfside / 2;
 headwidth = halfside / 2;
 eyesize = halfside / 10;
 neck = halfside / 4;
 d = 1000;
 ra1 =  halfside;
 rb1 =  5*halfside/4;
 REx = headwidth / 4;
 REy = (5*halfside)/8;
 REz = -halfside + halfside / 8;
 LEx = -REx; LEy = REy; LEz = REz;
 SHx =  halfside / 2; SHy =   0; SHz = -halfside;
 FIx =  TAx; FIy = TAy; FIz = TAz;
 i3a = 0; i3e = 0; i3d = 0;
 %initdynam();
end