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
	int cr = getLine("what is the derivative of the function (auto deriv calc will be added later)?\n", deriv, sizeof(deriv));
	if (cr == NO_INPUT)
	{
		printf("\nNO INPUT\n");
		return 1;
	}
	if (cr == TOO_LONG)
	{
		printf("Input too long [%s]\n", deriv);
		return 1;
	}

	//make a copy of the function to working function
	for (int i = 0; i < strlen(function); i++)
	{
		workingFunction[i] = function[i];
	}
	double result1 = compute(workingFunction, deriv, seedValue, 1);
	printf("How many times do you want to run the iteration?");
	int r = 0;
	scanf_s("%i", r);
	double result2 = compute(workingFunction, deriv, result1, r);
	//enter into api, return deriv into new array called deriv
	//first compute iteration here, everyone following is done using the function.
	//need to figure out how to use a web api without nuget shit.... dis iz prablem...
	getchar();

}

double compute(char function[128], char deriv[128], double value, int repeat)
{
	double done = 0;
	while (repeat >= 0)
	{
		double x;
		te_variable vars[] = { { "x", &x } };
		int err1;
		te_expr *func = te_compile(function, vars, 2, &err1);
		x = value;
		double h1 = te_eval(func); /* Returns 5. */
		te_free(func);

		int err2;
		te_expr *deriv = te_compile(deriv, vars, 2, &err2);
		x = value;
		double h2 = te_eval(deriv); /* Returns 5. */
		te_free(deriv);

		double s1 = h1 / h2;

		double done = done - s1;
		printf("%d", done);
	}
	return done;
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