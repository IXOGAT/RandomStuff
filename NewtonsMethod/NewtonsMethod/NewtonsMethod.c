//a = b - (f(b))/(f'(b))
//wolfram appid LVVLL6-38TP8YGUWP 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tinyexpr.h"
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
double a;
double b;

int main(void)
{

	const int seedValue = 1;
	char function[128] = "\0";
	char workingFunction[128] = "\0";
	char targetVar = 'x';
	//printf("What is the function that you want to find the zeros of?\n> ");
	//scanf_s("%127[^\n]", function);
	int rc = getLine("What is the function that you want to find the zeros of?\n> ", function, sizeof(function));
	if (rc == NO_INPUT) {
		// Extra NL since my system doesn't output that on EOF.
		printf("\nNo input\n");
		return 1;
	}

	if (rc == TOO_LONG) {
		printf("Input too long [%s]\n", function);
		return 1;
	}
	char deriv[128] = "\0";
	int targetVarPos[20];
	//find all x's in input string.
	int n = 0;
	for (int i = 0; i < strlen(function); i++)
	{
		if (function[i] == targetVar)
		{
			targetVarPos[n] = i;
			n++;
		}
	}
	//^^^ works currently. finds all x's and returns the indexes of them into the array targetVarPos
	//make a copy of the function.
	for (int i = 0; i < strlen(function); i++)
	{
		workingFunction[i] = function[i];
	}

	for (int i = 0; i < strlen(workingFunction); i++)
	{
		workingFunction[targetVarPos[i]] = seedValue;
	}
	//combine this and the function that finds the x's ez mode
	//enter into api, return deriv into new array called deriv

	//first compute iteration here, everyone following is done using the function.
	double r = te_interp(workingFunction, 0);
	printf("%f", r);
	//need to figure out how to use a web api without nuget shit.... dis iz prablem...
	getchar();

}

int compute(char function[128], char deriv[128])
{

}


static int getLine(char *prmpt, char *buff, size_t sz) {
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf("%s", prmpt);
		fflush(stdout);
	}
	if (fgets(buff, sz, stdin) == NULL)
		return NO_INPUT;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff) - 1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? TOO_LONG : OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff) - 1] = '\0';
	return OK;
}