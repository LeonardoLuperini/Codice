function y = myexp3(x, n)
  if x >= 0
    y = myexp2(x, n);
  else
    y = 1/myexp2(-x, n);
  endif
 end
