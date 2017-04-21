#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#define ZERO 48
#define TEN 10
using namespace std;
struct integer{
	char* number;
	int neg;
};
struct fraction{
	char* number;
	int size;
};
void XC(char* mant, char* exp, int bits);
int checker(const char* number);
char* read_string();
unsigned int dot_search(char* num);
int return_int(char char_num);
void calc_num(char* char_num, unsigned int dot, fraction& post_dot, integer& pre_dot);
void num_to_bin(char* pre_dot, char *bin_num);
void dec_to_bin(fraction& post_dot, char *bin_frac_num);
char* fexp32(const char *bin_num, const char *bin_frac_num);
char* exp_to_bin(int number, int bit);
char* fmant32(char* bin_num, char* bin_frac_num);
char* fmant64(char* bin_num, char* bin_frac_num);
char* fexp64(const char *bin_num, const char *bin_frac_num);
char* hex32(int neg, char* mant, char* exp, char* outp);
char* hex64(int neg, char* mant, char* exp, char* outp);
void check_zero(char* bin_num, char* bin_frac_num, int neg);
int inf_check(char* exp, int neg);
int main()
{
	char *num, bin_num[850], bin_frac_num[850], bin_frac_num2[850];
	char bin_frac_num3[850], bin_frac_num4[850];
	char *exp32, *mant32, *exp64, *mant64, *outp = new char[256];
	int dot_location;
	integer pre_dot;
	fraction post_dot;
	pre_dot.neg = 1;
	cout << "Number: ";
	num = read_string();
	dot_location = dot_search(num);
	pre_dot.number = (char*) malloc(dot_location * sizeof(char));
	post_dot.number = (char*) malloc(((strlen(num) - dot_location) + 1) * sizeof(char));
	calc_num(num, dot_location, post_dot, pre_dot);
	//num_to_bin(pre_dot, bin_num);
	dec_to_bin(post_dot, bin_frac_num);
	num_to_bin(pre_dot.number, bin_num);
	check_zero(bin_num, bin_frac_num, pre_dot.neg);
	//cout<<bin_num<<endl<<bin_frac_num<<endl<<endl;
	strcpy(bin_frac_num2, bin_frac_num);
	strcpy(bin_frac_num3, bin_frac_num);
	strcpy(bin_frac_num4, bin_frac_num);
	exp32 = fexp32(bin_num, bin_frac_num);
	if(inf_check(exp32, pre_dot.neg))
	{
		mant32 = fmant32(bin_num, bin_frac_num);
		hex32(pre_dot.neg, mant32, exp32, outp);
		cout<<"IEEE 32:\t"<<outp<<endl;
	}//if
	exp64 = fexp64(bin_num, bin_frac_num2);
	//cout<<"exp: "<<exp64<<endl;
	mant64 = fmant64(bin_num, bin_frac_num2);
	hex64(pre_dot.neg, mant64, exp64, outp);
	cout<<"IEEE 64:\t"<<outp<<endl;
	//cout<<"exp: "<<exp64<<endl;
	//cout<<"matn: "<<mant64<<endl;
	//cout<<"length: "<<strlen(mant64)<<endl<<mant64[52]<<endl;
	//cout<<"XC"<<endl;
	exp32 = fexp32(bin_num, bin_frac_num3);
	if(inf_check(exp32, pre_dot.neg))
	{
		mant32 = fmant32(bin_num, bin_frac_num3);
		//cout<<":"<<mant32<<":"<<exp32<<":"<<endl;
		XC(mant32, exp32, 32);
		hex32(pre_dot.neg, mant32, exp32, outp);
		cout<<"IEEE 32 XC:\t"<<outp<<endl;
	}//if
	exp64 = fexp64(bin_num, bin_frac_num4);
	//cout<<"exp: "<<exp64<<endl;
	mant64 = fmant64(bin_num, bin_frac_num4);
	XC(mant64, exp64, 64);
	hex64(pre_dot.neg, mant64, exp64, outp);
	cout<<"IEEE 64 XC:\t"<<outp<<endl;
	
	//cout << pre_dot.number * pre_dot.neg << endl << post_dot.number << endl << post_dot.size << endl;
	//cout<<bin_frac_num<<endl;
	return 0;
}//main
void XC(char* mant, char* exp, int bits)
{
	int location, i, exp_loc;
	if(bits == 32)
	{
		location = 23;
		exp_loc = 7;
		if(mant[location] == '0')
		return;
	}//if
	else
	{
		location = 52;
		exp_loc = 10;
		if(mant[location] == '0')
			return;
	}//else
	for(i = location - 1; i >= 0; i--)
	{
		if(mant[i] == '1')
			mant[i] = '0';
		else if(mant[i] == '0')
		{
			mant[i] = '1';
			break;
		}//if		
	}//for
	if(!i)
	{
		for(i = exp_loc; i >= 0; i--)
		{
			if(exp[i] == '1')
				exp[i] = '0';
			else if(exp[i] == '0')
			{
				exp[i] = '1';
				break;
			}//if
		}//for
	}//if
}//XC
int inf_check(char* exp, int neg)
{
	int i;
	for(i = 0; i < 8; i++)
	{
		if(exp[i] == '0')
			return 1;
	}
	if(neg == 1)
		cout<<"IEEE 32:     "<<"7F800000"<<endl;
	else
		cout<<"IEEE 32:     "<<"FF800000"<<endl;
	return 0;
}//end
void check_zero(char* bin_num, char* bin_frac_num, int neg)
{
	int i;
	for(i = 0; i < 849; i++)
	{
		if(bin_num[i] == '1')
			return;
	}
	for(i = 0; i < 849; i++)
	{
		if(bin_frac_num[i] == '1')
			return;
	}
	if(neg == 1)
	{
		cout<<"IEEE 32:     "<<"00000000"<<endl;
		cout<<"IEEE 64:     "<<"0000000000000000"<<endl;
	}
	else
	{
		cout<<"IEEE 32:     "<<"80000000"<<endl;
		cout<<"IEEE 64:     "<<"8000000000000000"<<endl;
	}
	exit(0);
}//check_zero
char* hex64(int neg, char* mant, char* exp, char* outp)
{
	char bin[65], hex1[17], temp[4];
	int bits, i;
	hex1[16] = '\0';
	if(neg == 1)
		bin[0] = '0';
	else
		bin[0] = '1';
	strncat(bin, exp, 11);
	strncat(bin, mant, 52);
	for(i = 0; i < 16; i++)
	{
		strncpy(temp, bin + (i * 4), 4);
		bits = (temp[0] - ZERO) * 8 + (temp[1] - ZERO) 
		* 4 + (temp[2] - ZERO) * 2 + (temp[3] - ZERO);
		if(bits < 10)
			hex1[i] = bits + ZERO;
		else
			hex1[i] = 17 + ZERO + (bits - 10);
	}//for
	//cout<<"IEEE 64";
	//printf("%s\n", hex1);
	strcpy(outp, hex1);
	return outp;
}
char* fmant64(char* bin_num, char* bin_frac_num)
{
	char *mant;
	int i, dummy = 0;
	int location = 0;
	mant = new char[54];
	mant[53] = '\0';
	for(i = 0; i < 54; i++)
		mant[i] = '0';
	for(i = 0; i < 849; i++)
	{
		if(bin_num[i] == '1')
		{
			location = 1 + i;
			break;
		}
		if(i == 848)
			if(bin_num[i] == '0')
				location = 849;
	
	}//for
	if(location == 849)
	{
		for(i = 0; i < 849; i++)
		{
			if(bin_frac_num[i] == '1')
			{
				bin_frac_num[i] = '0';
				break;
			}
		}
	}
	if(location <= 849)
	{
		strncpy(mant, bin_num + location, 53);
	}//if
	if((52 - (849 - location)) > 0)
	{
		if(location == 849)
			dummy = 1;
		strncat(mant, bin_frac_num + dummy, 52 - (848 - location));
		//if(location == 64)
			//mant[22] = '0';
	}
	return mant;
}//end of fmat
char* fexp64(const char* bin_num, const char* bin_frac_num)
{
	int i;
	int power = 0;
	for(i = 0; i < 849; i++)
	{
		if(bin_num[i] == '1')
		{
			power = 849 - i;
			break;
		}
	}//for
	if(i == 849)
	{
		i = 0; 
		for(i = 0; i < 849; i++)
		{
			if(bin_frac_num[i] == '1')
			{
				power = 0 - i;
				break;
			}
		}
	}
	return exp_to_bin(power + 1022, 11);
}//exp32
char* hex32(int neg, char* mant, char* exp, char* outp)
{
	char bin[33], hex1[9], temp[4];
	int bits, i;
	hex1[8] = '\0';
	if(neg == 1)
		bin[0] = '0';
	else
		bin[0] = '1';
	strncat(bin, exp, 8);
	strncat(bin, mant, 23);
	for(i = 0; i < 8; i++)
	{
		strncpy(temp, bin + (i * 4), 4);
		bits = (temp[0] - ZERO) * 8 + (temp[1] - ZERO) 
		* 4 + (temp[2] - ZERO) * 2 + (temp[3] - ZERO);
		if(bits < 10)
			hex1[i] = bits + ZERO;
		else
			hex1[i] = 17 + ZERO + (bits - 10);
	}//
	//cout<<hex1;
	//cout<<"IEEE 32";
	//printf("%s\n", hex1);//cout<<hex1<<endl;
	strcpy(outp, hex1);
	return outp;
}
char* fmant32(char* bin_num, char* bin_frac_num)
{
	char *mant;
	int i, dummy = 0;
	int location = 0;
	mant = new char[25];
	mant[24] = '\0';
	for(i = 0; i < 24; i++)
		mant[i] = '0';
	for(i = 0; i < 849; i++)
	{
		if(bin_num[i] == '1')
		{
			location = 1 + i;
			break;
		}
		if(i == 848)
			if(bin_num[i] == '0')
				location = 849;
	
	}//for
	if(location == 849)
	{
		for(i = 0; i < 849; i++)
		{
			if(bin_frac_num[i] == '1')
			{
				bin_frac_num[i] = '0';
				break;
			}
		}
	}
	if(location <= 849)
	{
		strncpy(mant, bin_num + location, 24);
	}//if
	if((23 - (849 - location)) > 0)
	{
		if(location == 849)
			dummy = 1;
		strncat(mant, bin_frac_num + dummy, 23 - (848 - location));
		//if(location == 64)
			//mant[22] = '0';
	}
	return mant;
}//end of fmat
char* exp_to_bin(int number, int bit)
{
	char *bin;
	bin = (char*) malloc((bit + 1) * sizeof(char));
	int i;
	for(i = 0; i < bit; i++)
		bin[i] = '0';
	bin[bit] = '\0';
	i = bit - 1;
	if(((number - 126) > 128) && (bit == 8))
	{
		for(i = 7; i >= 0; i--)
			bin[i] = '1';
		return bin;
	}
	while(number != 0)
	{
		bin[i] = (number % 2) + ZERO;
		number = number / 2;
		i--;
	}//while
	return bin;
}//function
char* fexp32(const char* bin_num, const char* bin_frac_num)
{
	int i;
	int power = 0;
	for(i = 0; i < 849; i++)
	{
		if(bin_num[i] == '1')
		{
			power = 849 - i;
			break;
		}
	}//for
	if(i == 849)
	{
		i = 0; 
		for(i = 0; i < 849; i++)
		{
			if(bin_frac_num[i] == '1')
			{
				power = 0 - i;
				break;
			}
		}
	}
	return exp_to_bin(power + 126, 8);
}//exp32
unsigned int dot_search(char* num)
{
	unsigned int i;
	for(i = 0; i < strlen(num); i++)
	{
		if(num[i] == '.')
			return i;
	}
	return 0;
}//search
void dec_to_bin(fraction& post_dot, char *bin_frac_num)
{
	int carry = 0, i;
	int length = strlen(post_dot.number) - 1;
	char* temp = post_dot.number;
	int binary_num_index = 0;
	bin_frac_num[849] = '\0';
	for(int i = 0; i < 849; i++)
		bin_frac_num[i] = '0';
	while(checker(temp) && binary_num_index < 849)
	{
		carry = 0;
		for(i = length; i >= 0; i--)
		{
			if((((temp[i] - ZERO) * 2) + carry) > 9)
			{
				
				temp[i] = (((temp[i] - ZERO) * 2) - 10 + carry) + ZERO;
				carry = 1;
			}
			else
			{
				temp[i] = ((temp[i] - ZERO) * 2) + carry + ZERO;
				carry = 0;
			}
			if((i - 1 < 0) && carry == 0)
			{
				bin_frac_num[binary_num_index] = '0';
				binary_num_index++;
			}
			if((i - 1 < 0) && carry == 1)
			{
				bin_frac_num[binary_num_index] = '1';
				binary_num_index++;
				carry = 0;
			}
			//EXTRA CREDIT HERE
			//carry = 0;
		}//for
	}//while
}//convert frac to bin*/
void num_to_bin(char* pre_dot, char *bin_num){
	unsigned int i = 0;
	char a;
	int binary_num_index = 848, start = 0;
	unsigned int carry = 0, length;
	char* temp;
	bin_num[849] = '\0';
	for(i = 0; i < 849; i++)
		bin_num[i] = '0';
	temp = pre_dot;
	length = strlen(temp);
	while(checker(temp) && binary_num_index >= 0)
	{
		bin_num[binary_num_index] = ((pre_dot[strlen(pre_dot) - 1] - ZERO) & 1) + ZERO;
		binary_num_index--;
		carry = 0;
		for(i = start; i < length; i++)
		{
			a = temp[i];
			temp[i] = ((temp[i] - ZERO) / 2) + ZERO;
			if(temp[i + 1] != '\0')
				temp[i + 1] = ((((a - ZERO) - (2 * (temp[i] - ZERO))) * 10) + (temp[i + 1] - ZERO)) + ZERO;
		}
	}
	/*while(checker(pre_dot.number) && binary_num_index >= 0)
	{
		bin_num[binary_num_index] = ((pre_dot.number[strlen(pre_dot.number) - 1] - ZERO) & 1) + ZERO;
		binary_num_index--;
		carry = 0;
		for(i = start; i < length; i++)
		{

			if(temp[i] - ZERO < 2)
			{
				carry = 10;
				if(temp[i] != '0')
				{	
					temp[i] = 'q';
					start++;
				}
				if(!(temp[i + 1] == '\0'))
					temp[i + 1] = (temp[i + 1] - ZERO) + 10 + ZERO;
				//start++;
			}
			else
			{
				temp[i] = ((temp[i] - ZERO) / 2) + ZERO;
				if(temp[i] == '0')
					temp[i] = 'q';
				carry = 0;
			}
		}//for
	}*/
}
void calc_num(char* char_num, unsigned int dot, fraction& post_dot, integer& pre_dot)
{
	unsigned int index_original = 0, index_new = 0;
	int count = 0,  start = 0;
	if(char_num[0] == '-')
	{
		pre_dot.neg = -1;
		start = 1;
	}//if
	for(index_original = start; index_original < dot; index_original++)
	{
		pre_dot.number[index_new] = char_num[index_original];
		index_new++;
	}//for
	pre_dot.number[index_new] = '\0';
	index_original++;
	index_new = 0;
	for(index_original = index_original; index_original < strlen(char_num); index_original++)
	{
		post_dot.number[index_new] = char_num[index_original];
		index_new++;
		count++;
	}//for
	post_dot.number[index_new] = '\0';
	post_dot.size = count;
}//dot search
int checker(const char* number)
{
	unsigned int i = 0;
	for(i = 0; i < (strlen(number)); i++)
	{
		if(number[i] != '0')
			return 1;
	}
	return 0;
}//checker
char* read_string()
{
	char *num, scan;
	int i = 0;
	num = (char*) malloc(256 * sizeof(char));
	while((scan = getchar()) != '\n')
	{
		num[i] = scan;
		num[i + 1] = '\0';
		i++;
	}//while
	return num;
}
int return_int(char char_num)
{
	return char_num;
}//return_int
