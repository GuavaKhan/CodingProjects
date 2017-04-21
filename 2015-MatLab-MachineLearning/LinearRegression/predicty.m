%Input: x, our matrix of independent variable(s)
%	w, our matrix of weights
%Output: y, our predicted y values
function [y] = predicty(x,w)
	y = x * w;
endfunction
