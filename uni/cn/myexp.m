function y = myexp(x, n)
  y = 1;
  for i = 1:n
    y = y + potenza(x,i)/fact(i);
  endfor
 end

