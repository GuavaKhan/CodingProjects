// pktemple; Temple, Parker

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
using namespace std;

int calculate(int *nums, int numcount, char *ops, int opcount);

int main()
{
	char *inp = new char[400], ops[80], *ptr = new char[80]; 
  int nums[80];
	int numcount = 0, opcount = 0, ans = 0;
	
	fgets(inp, 400, stdin);
	ptr = strtok(inp, " \n\t\r\0");

	while(ptr != NULL)
	{
		if(isdigit(ptr[0]) || (ptr[0] == '-' && isdigit(ptr[1])))
		{
			nums[numcount] = atoi(ptr);
			numcount++;
		}//if isdigit
		else//if ptr is not an integer
			if(ptr[0] == '+' || ptr[0] == '-' || ptr[0] == '/' || ptr[0] == '*')
			{
				ops[opcount] = (char) ptr[0];
				opcount++;
			}//if ptr is an operator

		ptr = strtok(NULL, " \n\t\r\0");
	}//while
	
	ans = calculate(nums, numcount, ops, opcount);

	cout << ans << endl;
  return 0;
}//main

int calculate(int *nums, int numcount, char *ops, int opcount)
{
	int ans = 0, i = numcount, j = 0;
	for(j = 0; j < opcount; j++)
	{
		switch(ops[j])
		{
			case '+': ans = nums[numcount - i] + nums[numcount - i + 1]; break;
			case '-': ans = nums[numcount - i] - nums[numcount - i + 1]; break;
			case '*': ans = nums[numcount - i] * nums[numcount - i + 1]; break;
			case '/': ans = nums[numcount - i] / nums[numcount - i + 1]; break;
			default: cout << "Unthinkable error occurred with operator" << endl;
		}//switch
		nums[numcount - i + 1] = ans;
		i--;
	}//for

	return ans;
}//calculate
