%Input: x, our matrix of independent variable(s)
%	w, our matrix of weights
%Output: y, our predicted y values
function [y] = logpredicty(x,w)
	n = x * w;
	e = exp(1);
	y = power(e,n) / (power(e,n) + 1);
endfunction
