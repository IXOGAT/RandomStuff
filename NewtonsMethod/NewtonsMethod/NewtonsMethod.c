//a = b - (f(b))/(f'(b))
//wolfram appid LVVLL6-38TP8YGUWP 
#include <stdio.h>
#include <stdlib.h>
double a;
double b;

int main(void)
{

	int seedValue = 0;
	char function[128] = "\0";
	char targetVar;
	printf("What is the function that you want to find the zeros of?\n> ");
	scanf_s("%s", function);
	printf("Please enter the target variable of choice: ");
	char deriv[128] = "\0";
	//enter into api, return deriv into new array called deriv

	//first compute iteration here, everyone following is done using the function.

	double s1;
	double s2;
	double s3;
	double s4;
	double s5;
	b = seedValue;
	//need to figure out how to use a web api without nuget shit.... dis iz prablem...

}

int compute(char function[128], char deriv[128])
{

}