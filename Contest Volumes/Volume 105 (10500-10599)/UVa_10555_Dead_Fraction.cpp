
/*
	UVa 10555 - Dead Fraction

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10555_Dead_Fraction.cpp

	from Waterloo local contest, 27 September, 2003, Problem B
		(http://acm.student.cs.uwaterloo.ca/~acm00/030927/data/)
*/

#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

long long gcd(long long x, long long y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int get_number(const char* s, const char* e)
{
	int n = 0;
	for ( ; s < e; s++)
		n = n * 10 + *s - '0';
	return n;
}

int main()
{
	const int nr_digits_max = 9;
	long long pow10s[nr_digits_max + 1] = {1};
	for (int i = 1; i <= nr_digits_max; i++)
		pow10s[i] = pow10s[i - 1] * 10;
	while (true) {
		char s[16];
		scanf("%s", s);
		if (!s[1])
			break;
		const char *ps = &s[2], *pe = strchr(ps, '.');
		long long min_denominator = numeric_limits<int>::max(), min_numerator;
		for (const char* p = ps; p < pe; p++) {
			int non_periodic = get_number(ps, p), periodic = get_number(p, pe);
			long long numerator = (pow10s[pe - p] - 1) * non_periodic + periodic,
				denominator = pow10s[p - ps] * (pow10s[pe - p] - 1);
			long long g = gcd(numerator, denominator);
			denominator /= g;
			if (denominator < min_denominator)
				min_denominator = denominator, min_numerator = numerator / g;
		}
		printf("%lld/%lld\n", min_numerator, min_denominator);
	}
	return 0;
}

