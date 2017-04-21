%single variable linear regression. minimum order of 2
%Input: x, our matrix of independent training variables
%	y, our matrix of our dependent training variable
%	xt, our matrix of independent testing variables
%	yt, our matrix of our dependent testing variable
%	trainq, the number of samples in our training matrices
%	testq, the number of samples in our testing matrices
%	order, the order we wish to regress to, minimum 2
%	newsample, the newsample from problem 7 we wish to predict
function [] = plotregress(x,y,xt,yt,trainq, testq,order, newsample)
	%plot our scatter plot
	plot(xt,yt,'k.', 'Markersize', 3);

	%normalize x
	xo = ones(length(x),1);
	xn = [xo, x];

	%initialize our array of RMS errors
	sostrain = zeros(order+1,1)';
	sostest = zeros(order+1,1)';

	%normalize xt
	xto = ones(length(xt),1);
	xtn = [xto, xt];

	%create a matrix of evenly spaced x values from min(x) to max(x) in 1000 increments
	step = (max(x) - min(x))/1000;
	z = [min(x):step:max(x)]';
	zo = ones(length(z),1);
	zn = [zo, z]; %normalize z matrix

	hold on;
	%draw our 0th order line
	w = findols(xo,y);
	py = predicty(zo,w);
	plot(z, py);
	
	%calculate our train/test y's and error for 0th order
	pytrain = predicty(xo, w);
	pytest = predicty(xto, w);
	sostrain(1) = sumofsquares(y, pytrain);
	sostest(1) = sumofsquares(yt, pytest);

	%draw our 1st order line
	w = findols(xn,y);
	py = predicty(zn,w);
	plot(z, py);

	%calculate our train/test y's and error for 1th order
	pytrain = predicty(xn, w);
	pytest = predicty(xtn, w);
	sostrain(2) = sumofsquares(y, pytrain);
	sostest(2) = sumofsquares(yt, pytest);

	for i = 2:order,
		%draw our 2 through order'th order lines
		polyxn = makepoly(xn, i);
		w = findols(polyxn, y);
		polyz = makepoly(zn, i);
		py = predicty(polyz, w);
		plot(z,py);

		%calculate our train/test y's and error for 2 through order'th orders
		polyxt = makepoly(xtn, i);
		pytrain = predicty(polyxn, w);
		pytest = predicty(polyxt, w);
		sostrain(i+1) = sumofsquares(y, pytrain);
		sostest(i+1) = sumofsquares(yt, pytest);
	end
	axis([min(x) max(x) min(y) max(y)]) %make x and y axes centered on the range we care about: min(x) to max(x), min(y) to max(y)
	hold off;

	%calculate our RMS errors
	for i = 1:(order+1),
		sostrain(i) = sqrt(sostrain(i) / trainq);
		sostest(i) = sqrt(sostest(i) / testq);
	end

	disp(['Root Mean Squared Training Error for polynomials degrees 0 through ' num2str(order)])
	disp(sostrain)
	disp(['Root Mean Squared Testing Error for polynomials degrees 0 through ' num2str(order)])
	disp(sostest)
endfunction
