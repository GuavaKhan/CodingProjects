%input: data, all of our samples
%	low, all of our low mpg samples
%	med, all of our medium mpg samples
%	high, all of our high mpg samples
%	attribs, the names of our attributes
%	numfigs, the number of plots we have created so far
function scatterplotter(data, low, med, high, attribs, numfigs)
numattributes = length(data(1,:));
numplots = 1;
%generates our 2d scatterplot
for i=1:8,
	for j=1:8,
		subplot(8,8, numplots);
		if i == j,
			hist(data(:,i));
		else,
			plot(low(:,j),low(:,i), 'b.', 'Markersize', 4);
			hold on
			plot(med(:,j),med(:,i), 'g.', 'Markersize', 4);
			plot(high(:,j),high(:,i), 'r.', 'Markersize', 4);
			hold off
		end
		if i == 1,
			title(attribs(j));
		end
		if j == 1,
			ylabel(attribs(i));
		end
		set(gcf, 'visible', 'off');
		set(gca,'XTick', []);
		set(gca,'YTick', []);
		numplots += 1;
	end
end
%scatter plot generation is done, now we save to file
fig = figure(numfigs);
saveas(fig, './2dscatterplot.png', 'png');
endfunction
