%this function reads in yeast.data
function [x,y] = readfile(filename)
	printf('\nLoading data');
	inpfile = 'yeast.data';
	inp = fopen(inpfile, 'r');
	x = [];
	y = [];
	while(true)
		line = fgetl(inpfile);
		if(line == -1)
			break;
		end
		toks = strsplit(line, " ");
		toklen = length(toks);
		r = [];
		for i = toks
			n = str2num(i{1});
			if length(n) != 0
				r = [r n];
			else
				yv = zeros(10,1)';
				switch(i{1})
					case "CYT"
						yv(1) = 1;
						y = [y; yv];
					case "NUC"
						yv(2) = 1;
						y = [y; yv];
					case "MIT"
						yv(3) = 1;
						y = [y; yv];
					case "ME3"
						yv(4) = 1;
						y = [y; yv];
					case "ME2"
						yv(4) = 1;
						y = [y; yv];
					case "ME1"
						yv(6) = 1;
						y = [y; yv];
					case "EXC"
						yv(7) = 1;
						y = [y; yv];
					case "VAC"
						yv(8) = 1;
						y = [y; yv];
					case "POX"
						yv(9) = 1;
						y = [y; yv];
					case "ERL"
						yv(10) = 1;
						y = [y; yv];
					otherwise
				endswitch
			endif
		endfor
		x = [x ; r];
	end
	printf('...done\n');
endfunction
