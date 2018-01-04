
/*
	UVa 11878 - Homework Checker

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11878_Homework_Checker.cpp
*/

#include <cstdio>
#include <cstdlib>

int main()
{
	const int nr_chars_max = 3 + 1 + 3 + 1 + 3;
	char s[nr_chars_max + 1];
	int correct_answers = 0;
	while (scanf("%s", s) != EOF) {
		char* p;
		int a = strtol(s, &p, 10);
		char op = *p++;
		int b = strtol(p, &p, 10);
		p++;
		if (*p != '?') {
			int c = strtol(p, NULL, 10);
			if (op == '+' && a + b == c ||
				op == '-' && a - b == c)
				correct_answers++;
		}
	}
	printf("%d\n", correct_answers);
	return 0;
}

