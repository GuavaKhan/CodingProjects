%multivariable linear regression. minimum order of 2
%Input: x, our matrix of independent training variables
%	y, our matrix of our dependent training variable
%	xt, our matrix of independent testing variables
%	yt, our matrix of our dependent testing variable
%	trainq, the number of samples in our training matrices
%	testq, the number of samples in our testing matrices
%	order, the order we wish to regress to, minimum 2
%	newsample, the newsample from problem 7 we wish to predict
function [] = regressmultivar(x,y,xt,yt, trainq, testq, order, newsample)
	%normalize x
	xo = ones(length(x),1);
	xn = [xo, x];

	%initialize our array of RMS errors
	sostrain = zeros(order+1,1)';
	sostest = zeros(order+1,1)';

	%normalize xt
	xto = ones(length(xt),1);
	xtn = [xto, xt];

	%predict y's and calculate error for degree 0. Predict new sample for degree 0
	w = findols(xo,y);
	pytrain = predicty(xo, w);
	pytest = predicty(xto, w);
	sostrain(1) = sumofsquares(y, pytrain);
	sostest(1) = sumofsquares(yt, pytest);
	newsampleO = [1];
	newsampleOPY = predicty(newsampleO, w);

	%predict y's and calculate error for degree 1. Predict new sample for degree 1
	w = findols(xn,y);
	pytrain = predicty(xn, w);
	pytest = predicty(xtn, w);
	sostrain(2) = sumofsquares(y, pytrain);
	sostest(2) = sumofsquares(yt, pytest);
	newsampleN = [1, newsample];
	newsampleNPY = predicty(newsampleN, w);

	%predict y's and calculate error for degrees 2:order. Predict new sample for degrees 2:order
	for i = 2:order,
		polyxn = makepolymultivar(xn, i, 7);
		w = findols(polyxn, y);
		polyxt = makepolymultivar(xtn, i, 7);
		pytrain = predicty(polyxn, w);
		pytest = predicty(polyxt, w);
		sostrain(i+1) = sumofsquares(y, pytrain);
		sostest(i+1) = sumofsquares(yt, pytest);
		newsamplePolyN = makepolymultivar(newsampleN, i, 7);
		newsamplePolyNPY = predicty(newsamplePolyN, w);
	end

	%Calculate root mean square from the sum of squares values we obtained
	for i = 1:(order+1),
		sostrain(i) = sqrt(sostrain(i) / trainq);
		sostest(i) = sqrt(sostest(i) / testq);
	end

	disp(['Root Mean Squared Training Error for polynomials degrees 0 through ' num2str(order)])
	disp(sostrain)
	disp(['Root Mean Squared Testing Error for polynomials degrees 0 through ' num2str(order)])
	disp(sostest)

	disp(['Predicted mpg for our new sample, orders 0 through ' num2str(order)]);
	disp([newsampleOPY, newsampleNPY, newsamplePolyNPY]);

endfunction
