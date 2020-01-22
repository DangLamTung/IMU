function [] = draw_ellipsoid(v_1,v_2)
figure
[a,b,c]= meshgrid(-3:0.02:3);
v= v_1(1)*a.^2 + v_1(2)*b.^2 + v_1(3)*c.^2 + 2*v_1(6)*b.*c + 2*v_1(5)*a.*c + 2*v_1(4)*a.*b+ v_2(1)*a + v_2(2)*b + v_2(3)*c + v_2(4) ;
isosurface(a,b,c,v,0);
end