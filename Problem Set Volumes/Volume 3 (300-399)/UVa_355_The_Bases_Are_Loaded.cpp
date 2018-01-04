
/*
	UVa 355 - The Bases Are Loaded

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_355_The_Bases_Are_Loaded.cpp
*/

#include <cstdio>
#include <cctype>

const int nr_digits_max = 10;

long long convert_from_string(const char* s, int base)
{
	long long n = 0;
	for (const char* p = s; *p; p++) {
		if (p > s)
			n *= base;
		char c = *p;
		if (isdigit(c)) {
			if (c - '0' >= base)
				return -1;
			n += c - '0';
		}
		else if (isupper(c)) {
			if (base <= 10 || c - 'A' + 10 >= base)
				return -1;
			n += c - 'A' + 10;
		}
		else
			return -1;
	}
	return n;
}

char* convert_to_string(long long n, int base, char* s)
{
	char* p = s + nr_digits_max * 4;
	*p-- = '\0';
	while (true) {
		long long m = n % base;
		if (m > 9)
			*p = m - 10 + 'A';
		else
			*p = m + '0';
		n /= base;
		if (!n)
			break;
		p--;
	}
	return p;
}

int main()
{
	int from, to;
	char converted_from[nr_digits_max + 1];
	while (scanf("%d %d %s", &from, &to, converted_from) != EOF) {
		long long n = convert_from_string(converted_from, from);
		if (n >= 0) {
			char converted_to[nr_digits_max * 4 + 1];
			char* p = convert_to_string(n, to, converted_to);
			printf("%s base %d = %s base %d\n", converted_from, from, p, to);
		}
		else
			printf("%s is an illegal base %d number\n", converted_from, from);
	}
	return 0;
}

