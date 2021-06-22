function [MEx,MEy,MEz,SHx,SHy,SHz] = body()

% Make Face cube
X = [0,1,1,0,0];Y = [0,0,1,1,0];Z = [0,0,0,0,0];

% plot3(X,Y,Z,'-or');
face = AxelRot([X;Y;Z],90,[1 0 0],[]);

hold on;
% Put Pipils and Mid Eye
% Eyes, Left, Right and Mid
LEx = 0.25; REx = 0.75; MEx = 0.5;
LEy = 0;    REy = 0;    MEy = 0;
LEz = 1.75; REz = 1.75; MEz = 1.75;

plot3(LEx,LEy,LEz,'or','LineWidth',1.5);
plot3(REx,REy,REz,'or','LineWidth',1.5);
plot3(MEx,MEy,MEz,'ob','LineWidth',1.5);
% Make Neck
Xn = [0.5,0.5]; Yn = [0.0,0.0]; Zn = [0.0,-1.0];
% plot3(Xn,Yn,Zn,'-*k','LineWidth',1.5);

% Make Shoulder
Xs = [-0.5,1.5];Ys = [0,0];Zs = [-1,-1];
% %neck = [Xs;Ys;Zs];
% plot3(Xs,Ys,Zs,'-*b','LineWidth',1.5);

% Make Body
Xb = [-0.5,0.5,0.5,1.5];Yb = [0,0,0,0];Zb = [-1,-2.5,-2.5,-1];
%body = [Xb;Yb;Zb];
% plot3(Xb,Yb,Zb,'-*m','LineWidth',1.5);

% Plot the Body Only Once
plot3(face(1,:),face(2,:)+2.5,face(3,:),'-or','LineWidth',1.5);
% Face
plot3(face(1,:),face(2,:),face(3,:)+1,'-ob','LineWidth',1.5);
% Eyes Box
plot3((face(1,:)/3)+0.075,(face(2,:)/3)-0.01,((face(3,:)/3)+0.5)+1,'-.r','LineWidth',1.5);
plot3((face(1,:)/3)+0.60,(face(2,:)/3)-0.01,((face(3,:)/3)+0.5)+1,'-.r','LineWidth',1.5);
% Neck
plot3(Xn,Yn,Zn+1,'-*k','LineWidth',1.5);
% Shoulder
plot3(Xs,Ys,Zs+1,'-*b','LineWidth',1.5);
% Body
plot3(Xb,Yb,Zb+1,'-*m','LineWidth',1.5);
% %Shoulder Coordinates
SHx = 1.5; SHy = 0; SHz = 0;

end