%Input: x, our matrix of independent variable(s)
%	y, our matrix of our dependent variable
%Output: ols, our matrix of weights
function [ols] = findols(x,y)
	xt = transpose(x);
	ols = inv((xt * x)) * xt * y;
endfunction
