function bilinear(a,M)


x = size(a)

 y = [M;floor((M/x(1)*x(2)))];
   resized_img = zeros(y(1),y(2));
size(resized_img)
scalex = 10;
scaley = 2.5;

for i = 1:x(1)
   for j = 1:x(2)
       if scalex*i >0 && scaley*j >0
           resized_img(scalex*i,scaley*j) = a(i,j); 
       end
   end
end

 for i = 1:x(1)-1
    for j = 1:x(2)-1
 for k= 1:scalex-1
    
       resized_img(scalex*i + k,scaley*j) =....
           round((scalex - k)/(scalex)* resized_img(scalex*i,scaley*j) +....
           k/(scalex)* resized_img(scalex*(i+1),(scaley)*j));
       
        resized_img(scalex*i + k,scaley*(j+1)) =....
           round((scalex - k)/(scalex)* resized_img(scalex*i,scaley*(j+1)) +....
            k/(scalex)* resized_img(scalex*(i+1),scaley*(j+1)));
 end
    for k= 0:scalex 
       for h = 0:scaley 
             resized_img(scalex*i + k,scaley*j + h) =....
             round((scaley - h)/(scaley)* resized_img(scalex*i+k,scaley*j) +....
              (h)/(scaley)* resized_img(scalex*i+k,scaley*(j+1))); 
        end 
   end
    end
 end  
% % 
%   for i = 1:y(1)
%       for j = 1:y(2)
%              resized_img(i,j) = a(round(i/scalex),round(j/scaley));
%         
%       end
%   end
% % % 

imshow(resized_img,[])
end



