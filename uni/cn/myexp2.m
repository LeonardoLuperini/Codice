function y = myexp2(x, n)
  y = 1;
  term = 1;
  for i = 1:n
    term = term * (x/i);
    y = y + term;
  endfor
 end

