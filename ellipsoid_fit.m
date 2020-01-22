function [A,b] = ellipsoid_fit(x,y,z)
D = [x.*x
    y.*y
    z.*z
    2.*y.*z
    2.*x.*z
    2.*x.*y
    2.*x
    2.*y
    2.*z
    ones(size(x))];
size(D)
S = D*transpose(D)
size(S)
        S11 = S(1:6,1:6)
        S12 = S(1:6,7:10)
        S21 = S(7:10,1:6)
        S22 = S(7:10,7:10)
size(S11)
size(S12)
size(S21)
size(S22)
C =[[-1,  1,  1,  0,  0,  0],
     [ 1, -1,  1,  0,  0,  0],
     [ 1,  1, -1,  0,  0,  0],
     [ 0,  0,  0, -4,  0,  0],
     [ 0,  0,  0,  0, -4,  0],
     [ 0,  0,  0,  0,  0, -4]];
 

E = inv(C)*(S11 - S12*inv(S22)*S21)

[V,D] = eig(E)
[argvalue, argmax] = max(max(D))

v_1 = V(:,argmax)
v_2 = -inv(S22)*S21*v_1

M = [v_1(1) v_1(4) v_1(5),
     v_1(4) v_1(2) v_1(6),
     v_1(5) v_1(6) v_1(3)]
n = [v_2(1)
     v_2(2)
     v_2(3)]
d = v_2(4)
sph = [[1 0 0 0],
       [0 1 0 0],
       [0 0 1 0],
       [0 0 0 -1]]

Q = [[M n];
    [transpose(n) d]];
A_ = inv(Q)*sph
A = 1/sqrtm(transpose(n)*inv(M)*n - d)*sqrtm(M)
b = -inv(M)*n

end