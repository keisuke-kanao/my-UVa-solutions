
/*
	UVa 11530 - SMS Typing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11530_SMS_Typing.cpp
*/

#include <cstdio>
#include <cctype>

const int nr_letters = 26;
const int nr_types[nr_letters] = { // nr_types[i] is the number of types for the letter of ('a' + i)
	1, 2, 3,
	1, 2, 3,
	1, 2, 3,
	1, 2, 3,
	1, 2, 3,
	1, 2, 3, 4,
	1, 2, 3,
	1, 2, 3, 4
};

int main()
{
	int t;
	scanf("%d", &t);
	getchar();
	for (int c = 1; c <= t; c++) {
		const int nr_chars_max = 100;
		char s[nr_chars_max + 1];
		gets(s);
		int n = 0;
		for (const char* p = s; *p; p++) {
			if (isspace(*p))
				n++;
			else
				n += nr_types[*p - 'a'];
		}
		printf("Case #%d: %d\n", c, n);
	}
	return 0;
}

