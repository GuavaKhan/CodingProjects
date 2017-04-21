source('scatterplotter.m');
source('findmpgratings.m');
source('findols.m');
source('plotregress.m');
source('makepoly.m');
source('predicty.m');
source('sumofsquares.m');
source('makepolymultivar.m');
source('regressmultivar.m');
source('logpredicty.m');
source('regresslog.m');

warning('off', 'all');

disp('Loading data')
data = load('auto-mpg.data');
disp('Data loaded')

attribs = {'mpg' 'cyls' 'displ' 'hp' 'weight' 'acc' 'yr' 'origin'};
mpg = data(:,1);
numfigs = 1;

newsample = [8, 300, 180, 3500, 9, 80, 1] %New sample from problem 7

%place each row of data into bins for low, medium, and high mpgs.
[mpgratings, low, med, high] = findmpgratings(data);
disp('mpg bins sorted')

%make the 2d scatter plot matrix
disp('Creating 2d scatter plot')
scatterplotter(data, low, med, high, attribs, numfigs);
numfigs += 1;
figure;
disp('2d scatter plot saved as 2dscatterplot.png')

%Plot 0th-10th polynomial linear regression for the 7 independent variables
printf('\nBeginning one variable linear regressions\n');
printf('---------------------------------------------');
for i = 2:8,
	subplot(4,2,(i-1));
	printf('\n%s\n', attribs{i});
	plotregress(data(1:300,i),mpg(1:300),data(301:392,i),mpg(301:392), 300, 92, 10, newsample);
	ylabel(num2str(i-1));
end
printf('\nOne variable linear regressions complete\n');

set(gcf, 'visible', 'off'); %prevents plot window from popping up. We just want to save as a png file.
%fig = figure(2);
fig = figure(numfigs);
saveas(fig, './linear.png', 'png');
set(gcf, 'visible', 'off');
disp('Linear regression plots saved as linear.png')


printf('\nBeginning multivariable linear regression\n');
printf('---------------------------------------------\n');
regressmultivar(data(1:300,2:end), mpg(1:300), data(301:392,2:end), mpg(301:392), 300, 92, 2, newsample);
printf('\nMultivariable linear regression complete\n');

%{
printf('\nBeginning 1st order logistic regression\n');
printf('---------------------------------------------\n');
regresslog(data(1:300,2:end), mpg(1:300), data(301:392,2:end), mpg(301:392), 92, newsample);
printf('\n1st order logistic regression complete\n');
%}

printf('\nProgram complete. press enter to quit.\n')
pause
