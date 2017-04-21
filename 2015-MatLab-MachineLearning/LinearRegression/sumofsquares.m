%Input:, y, matrix of our actual y values
%	py, matrix of our predicted y values
%Output: sos, our sum of squares
function [sos] = sumofsquares(y,py)
	sos = 0;
	for i = 1:length(py),
		sos += (y(i)-py(i))^2;
	end
endfunction
