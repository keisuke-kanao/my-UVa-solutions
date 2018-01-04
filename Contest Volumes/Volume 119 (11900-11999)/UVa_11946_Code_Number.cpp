
/*
	UVa 11946 - Code Number

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11946_Code_Number.cpp
*/

#include <cstdio>
#include <cctype>

int main()
{
	const char number_letters[] = {'O', 'I', 'Z', 'E', 'A', 'S', 'G', 'T', 'B', 'P'};
	int t;
	scanf("%d\n", &t);
	int c;
	while ((c = getchar()) != EOF)
		putchar((isdigit(c)) ? number_letters[c - '0'] : c);
	return 0;
}

