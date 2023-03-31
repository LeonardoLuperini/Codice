function [xnew] = GSstep(b, xold)
  n = length(b);
  xnew = zeros(n, 1);
  sumnew = 0;
  sumold = 0;

  for j = 2:n
    sumold = sumold + xold(j);
  endfor

  for i = 1:n
    if (i > 1)
      sumnew = sumnew + i*xnew(i-1);
    endif
    xnew(i) = (b(i) -sumnew -i*sumold)/i;
    if (i<n)
      sumold = sumold -xold(i+1);
    endif
  endfor
end
