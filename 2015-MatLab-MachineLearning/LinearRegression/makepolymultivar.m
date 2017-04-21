%Input: xn, our normalized matrix of independent variables
%	degree, the polynomial degree to make our new matrix
%Output: polyxn, xn raised to degree
function polyxn = makepolymultivar(xn, degree)
	polyxn = xn;
	for i = 2:degree,
		polyxn = [polyxn, power(polyxn(:,2:end), i)];
	end
endfunction
