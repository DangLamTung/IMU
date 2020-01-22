N = 1000;
 a = sqrt(6);
 b = sqrt(8);
 c = sqrt(6);
th = linspace(0,2*pi,N);
ph = linspace(0,pi,N);

R = ones(size(th));
x = a*sin(th).*cos(ph)+2;
y = b*sin(th).*sin(ph)+1;
z = c*cos(th)+5;
X = [x;y;z];
X_ = [x;y;z;ones(size(x))];
size(X);

% v_new



[ center, radii, evecs, v_new, chi2 ] = ellipsoid_fit_new(transpose(X));
[v_1,v_2,M,n,d] = ellipsoid_fit(x,y,z);
% 
size(n)

Q = [[M;transpose(n)],[n;d]]
sph = [[1 0 0 0],
       [0 1 0 0],
       [0 0 1 0],
       [0 0 0 -1]]
A_ = inv(Q)*sph
A = 1/sqrtm(transpose(n)*inv(M)*n - d)*sqrtm(M)
b = -inv(M)*n
mag_out = A*(X - b);

draw_ellipsoid([1,1,1,0,0,0],[0,0,0,-1]);
hold on
scatter3(mag_out(1,:),mag_out(2,:),mag_out(3,:));

size(mag_out);



% draw_ellipsoid(v_1,v_2);
% % 
% hold on
% scatter3(x,y,z)

