
/*
	UVa 10551 - Basic Remains

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10551_Basic_Remains.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int convert_to_decimal(int b, const char* n)
{
	int d = 0;
	for ( ; *n; n++) {
		d *= b;
		d += *n - '0';
	}
	return d;
}

void convert_to_string(int b, long long n, char* s)
{
	char* p = s;
	do {
		*p++ = '0' + n % b;
	} while (n /= b);
	*p = '\0';
	for (p--; s < p; s++, p--) // reverse the string
		swap(*s, *p);
}

int main()
{
	const int nr_digits_max = 1000;
	while (true) {
		int b;
		char p[nr_digits_max + 1], m[nr_digits_max + 1];
		scanf("%d", &b);
		if (!b)
			break;
		scanf("%s %s", p, m);
		int dm = convert_to_decimal(b, m);
		long long d = 0;
		for (const char* pp = p; *pp; pp++) {
			d *= b;
			d += *pp - '0';
			d %= dm;
		}
		convert_to_string(b, d, p);
		printf("%s\n", p);
	}
	return 0;
}

