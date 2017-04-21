%this randomly shuffles x and y together to randomize the training data
function [sx,sy] = shuffle(x,y)
	p = randperm(rows(x));
	sx = x(p,:);
	sy = y(p,:);
endfunction
