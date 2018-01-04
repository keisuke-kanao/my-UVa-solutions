
/*
	UVa 389 - Basically Speaking

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_389_Basically_Speaking.cpp

	from ACM Mid-Central Regionals 1995 Problem #5
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1995/index.html)
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_digits_max = 7;

int convert_from_string(const char* s, int base)
{
	int n = 0;
	for (const char* p = s; *p; p++) {
		if (p > s)
			n *= base;
		if (isdigit(*p))
			n += *p - '0';
		else
			n += 10 + *p - 'A';
	}
	return n;
}

char* convert_to_string(int n, int base, char* s)
{
	char* p = s + nr_digits_max;
	*p-- = '\0';
	while (true) {
		int m = n % base;
		if (m > 9)
			*p = m - 10 + 'A';
		else
			*p = m + '0';
		n /= base;
		if (!n)
			break;
		p--;
		if (p < s) {
			p = NULL; break;
		}
	}
	return p;
}

int main()
{
	int from, to;
	char converted_from[nr_digits_max + 1];
	while (scanf("%s %d %d", converted_from, &from, &to) != EOF) {
		int n = convert_from_string(converted_from, from);
		char converted_to[nr_digits_max + 1];
		char* p = convert_to_string(n, to, converted_to);
		if (p)
			printf("%7s\n", p);
		else
			printf("  ERROR\n");
	}
	return 0;
}

