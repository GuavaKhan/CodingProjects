%Uses code from the Deep Learning Toolbox: https://github.com/rasmusbergpalm/DeepLearnToolbox
addpath(genpath('DeepLearnToolbox'));
source('readfile.m');
source('shuffle.m');
source('predictsample.m');

[origx,origy] = readfile('yeast.data');
[x, y] = shuffle(origx,origy);

%Problem 3
disp("Problem 3: ");
trainingX = origx(1,:);%only running 1 sample
trainingY = origy(1,:);
%normalize the data
[trainingX, mu, sigma] = zscore(trainingX);

%setting up neural network
rand('state',0);
nn = nnsetup([(columns(x)) 3 columns(y)]);
nn.W{1,1} = ones(size(nn.W{1,1}));
nn.W{1,2} = ones(size(nn.W{1,2}));
nn.learningRate = .01;
opts.numepochs = 1;
opts.batchsize = 1;
opts.plot = 0;
opts.wtGraph = 0;

disp("First sample: ");
disp(trainingX)
disp(trainingY)
disp("Initial Weights");
disp(nn.W)
[nn, L] = nntrain(nn, trainingX, trainingY, opts);
disp("Updated Weights");
disp(nn.W)
disp("End Problem 3");

%Problem 1
disp("Problem 1:");
trainingLen = floor(rows(x)*.75);
trainingX = x(1:trainingLen,:);
trainingY = y(1:trainingLen,:);
testingX = x(trainingLen+1:end,:);
testingY = y(trainingLen+1:end, :);

[trainingX, mu, sigma] = zscore(trainingX);
testingX = normalize(testingX, mu, sigma);

rand('state',12345);
nn = nnsetup([(columns(x)) 3 columns(y)]);
nn.learningRate = .01;
opts.numepochs = 40;
opts.batchsize = 1;
opts.plot = 1;
opts.wtGraph = 1;

[nn, L] = nntrain(nn, trainingX, trainingY, opts);
[er, bad] = nntest(nn, testingX, testingY);
saveas(figure(1), './errorplot.png', 'png');
printf("Final Testing Error: %f\n", er);
disp("End Problem 1");

%Problem 2
printf("Problem 2:\n");
[zX, mu, sigma] = zscore(x);
normX = normalize(x, mu, sigma);
rand('state',0);
nn = nnsetup([(columns(x)) 3 columns(y)]);
nn.learningRate = .04;
opts.numepochs = 40;
opts.batchsize = 1;
opts.wtGraph = 0;
opts.plot = 0;

[nn, L] = nntrain(nn, zX, y, opts);
[er, bad] = nntest(nn, normX, y);
printf("Training Error: %f\n", er);

%Print out a_i equations in latex format for first weight vector
layer = 1;
wtVector = nn.W{layer};
disp("Activation function equations");
for r = 1:rows(wtVector)
	printf("$a_{%d}^{(%d)} = g(", r, layer+1);
	for c = 1:columns(wtVector)
		printf("%f \\cdot x_{%d}",wtVector(r,c),c-1);
		%printf("W_{%d,%d}^{(%d)} \\cdot x_{%d}",r,c-1,layer,c-1);
		if c != columns(wtVector)
			printf("+");
		end
	end
	printf(")$\n");
end
printf("\n");
%Print out a_i equations in latex format for second weight vector
layer = 2;
wtVector = nn.W{layer};
for r = 1:rows(wtVector)
	printf("$a_{%d}^{(%d)} = g(", r, layer+1);
	for c = 1:columns(wtVector)
		if c == 1
			printf("%f \\cdot x_{%d}",wtVector(r,c),c-1);
			%printf("W_{%d,%d}^{(%d)} \\cdot x_{%d}",r,c-1,layer,c-1);
			if c != columns(wtVector)
				printf("+");
			end
		else
			printf("%f \\cdot a_{%d}^{(%d)}",wtVector(r,c),c-1,layer);
			%printf("W_{%d,%d}^{(%d)} \\cdot a_{%d}^{(%d)}",r,c-1,layer,c-1,layer);
			if c != columns(wtVector)
				printf("+");
			end
		end
	end
	printf(")$\n");
end
disp("End Problem 2");

%Problem 5
disp("Problem 5: ");
unknown = [.5 .52 .52 .2 .6 0 .5 .29];
predictsample(unknown, nn);
disp("End Problem 5");


%Problem 4
disp("Problem 4:");
cx = columns(x);
cy = columns(y);
nns = [];
%run setups for the various neural network setups
nodenum = [3,5,8,10];
for i = 1:3
	for j = 1:4
		n = nodenum(j);
		if i == 1
			nns{i,j} = nnsetup([cx n cy]);
                        nns{i,j}.learningRate = .01;
		elseif i == 2
			nns{i,j} = nnsetup([cx n n cy]);
                        nns{i,j}.learningRate = .01;
		else
			nns{i,j} = nnsetup([cx n n n cy]);
                        nns{i,j}.learningRate = .01;
		end
	end
end
[zX, mu, sigma] = zscore(x);
normX = normalize(x, mu, sigma);
rand('state',0);
opts.numepochs = 40;
opts.batchsize = 1;
opts.plot = 0;
opts.wtGraph = 0;

errs = [];
for i = 1:3
	for j = 1:4
		printf("%d Hidden Layers: %d Nodes each\n", i, nodenum(j));
		[nns{i,j}, L] = nntrain(nns{i,j}, zX, y, opts);
		[er, bad] = nntest(nns{i,j}, normX, y);
		errs(i,j) = er;
	end
end
printf("3 by 4 matrix of errors: \n");
disp(errs)
disp("End Problem 4");
