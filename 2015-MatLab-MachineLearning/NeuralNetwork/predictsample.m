%This function takes in an unknown sample and nn, and uses nnpredict to determine which output node has the highest certainty.
%it prints out the predicted localization
function [] = predictsample(unknown, nn)
	[zU, mu, sigma] = zscore(unknown);
	normU = normalize(unknown, mu, sigma);
	prediction = nnpredict(nn,unknown);
	%[dummy, expected] = max(prediction,[],2);
	disp(prediction);
	site = [];
	switch(prediction)
		case 1
			site = "CYT";	
		case 2
			site = "NUC";	
		case 3
			site = "MIT";	
		case 4
			site = "ME3";	
		case 5
			site = "ME2";	
		case 6
			site = "ME1";	
		case 7
			site = "EXC";	
		case 8
			site = "VAC";	
		case 9
			site = "POX";	
		case 10
			site = "ERL";	
		otherwise
			site = "Unknown";
	end
	printf("Unknown sample prediction: %s\n", site);
endfunction
