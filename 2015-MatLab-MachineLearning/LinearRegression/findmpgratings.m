%Input: a matrix of our data
%Output: mpgratings, contains the classification for each sample in data,
%	 low, a matrix containing all samples with low mpg
%	 med, a matrix containing all samples with medium mpg
%	 high, a matrix containing all samples with high mpg
function [mpgratings, low, med, high] = findmpgratings(data)
	%initializations
	mpg = data(:,1);
	mpgratings = [];
	high = [];
	med = [];
	low = [];
	lowcount = 1;
	medcount = 1;
	highcount = 1;

	for i=1:length(mpg),
		if mpg(i) <= 18.5
			mpgratings{i} = 'low';
			low(lowcount,:) = data(i,:);
			lowcount = lowcount + 1;
		elseif mpg(i) <= 26.5
			mpgratings{i} = 'med';
			med(medcount,:) = data(i,:);
			medcount = medcount + 1;
		else
			mpgratings{i} = 'high';
			high(highcount,:) = data(i,:);
			highcount = highcount + 1;
		end
	end

	printf('\nLow MPG Bin Size: %d\n', length(low));
	printf('Medium MPG Bin Size: %d\n', length(med));
	printf('High MPG Bin Size: %d\n\n', length(high));
endfunction
