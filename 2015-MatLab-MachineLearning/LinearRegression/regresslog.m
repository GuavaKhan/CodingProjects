%1st order logistic regression
function [] = regresslog(x,y,xt,yt, quantity, newsample)
	xo = ones(length(x),1);
	xn = [xo, x];

	sostrain = zeros(1,1)';
	sostest = zeros(1,1)';

	xto = ones(length(xt),1);
	xtn = [xto, xt];

	w = findols(xn,y);
	pytrain = logpredicty(xn, w);
	pytest = logpredicty(xtn, w);
	pytest
	sostrain(1) = sumofsquares(y, pytrain);
	sostest(1) = sumofsquares(yt, pytest);

	sostrain(1) = sqrt(sostrain(1) / quantity);
	sostest(1) = sqrt(sostest(1) / quantity);

	disp('Root Mean Squared Training Error for polynomial degree 1')
	disp(sostrain)
	disp('Root Mean Squared Testing Error for polynomial degree 1')
	disp(sostest)

	newsampleN = [1, newsample];
	newsampleNPY = logpredicty(newsampleN, w);
	n = newsampleN * w
	e = exp(1);
	y = power(e,n) / (power(e,n) + 1)
	disp(['Predicted mpg for our new sample, order 1']);
	disp(newsampleNPY);

endfunction
