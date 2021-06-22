%% Makecube TG - Footscray 28-11-2019

function makecube(p1,p2,p3,p4,p5,p6,p7,p8)

poly_rectangle(p1, p2, p3, p4); 
hold on; 
poly_rectangle(p3, p4, p8, p7);
poly_rectangle(p1, p4, p8, p5)
poly_rectangle(p1, p5, p6, p2)
poly_rectangle(p2, p3, p7, p6)
poly_rectangle(p5, p6, p7, p8)
end