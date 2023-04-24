function [k,xk] = puntofisso(g, x0, tol)
  for k=1:100
    xk = g(x0);
    if (abs(x0 - xk) < tol)
      break;
    endif
    x0 = xk;
  endfor
end
