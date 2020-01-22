log_file_full = load('./data/EKF_stm32_m.txt');
starting_row = 1;
end_row = 1000;
log_file_test  = log_file_full(starting_row:end_row,:);
N = max(size(log_file_test)); % Size of tested sample
mag  = log_file_test(:,1:3);

figure

x = mag(:,1);
y = mag(:,2);
z = mag(:,3);
k = 1;
%filter 
x_ = zeros(1,N);
y_ = zeros(1,N);
z_ = zeros(1,N);
size(x_)
h = 1;
while k<N
%      if( (x(k)>-60 || x(k)< -480)|| (y(k)>400 || y(k)< -100) || (z(k)>200 || z(k)< -300))

%      else
        x_(h) = x(k);
        y_(h) = y(k);
        z_(h) = z(k);
        h = h + 1;
%     end
     k = k+1;
 end
x_ = x_(1:h-1);
y_ = y_(1:h-1);
z_ = z_(1:h-1);
[A,b] = ellipsoid_fit(x_,y_,z_)


% scatter3((x_ - offset_x)* scale_x ,(y_ -offset_y)* scale_y,(z_ -offset_z)* scale_z)
figure
subplot(3,1,1);
histogram(x)
subplot(3,1,2);
histogram(y)
subplot(3,1,3);
histogram(z)

% if(v_1(1)<0) 
%     v_1 = -v_1
% end
X_new = transpose([x_;y_;z_]);

[ center, radii, evecs, v_new, chi2 ] = ellipsoid_fit_new(X_new)
v_new;
% draw_ellipsoid(v_1,v_2)
% hold on
% scatter3(x_,y_,z_)
% axis tight
% draw_ellipsoid(v_new(1:6),v_new(7:10))
% figure
% subplot(3,1,1);
% histogram(x_)
% subplot(3,1,2);
% histogram(y_)
% subplot(3,1,3);
% histogram(z_)

mag_out = A*(transpose(mag) - b);

draw_ellipsoid([1,1,1,0,0,0],[0,0,0,-1]);
hold on
scatter3(mag_out(1,:),mag_out(2,:),mag_out(3,:));

std(mag)