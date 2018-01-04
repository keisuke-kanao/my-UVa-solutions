/*
	UVa 332 - Rational Numbers from Repeating Fractions

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_332_Rational_Numbers.cpp

	from ACM North Central Regionals 1994
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1994/prob_b.html)
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	const int nr_digits_max = 9;
	const int pow_10s[nr_digits_max + 1] = {
		1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
	};
	for (int case_nr = 1; ; case_nr++) {
		int j;
		scanf("%d", &j);
		if (j == -1)
			break;
		char s[nr_digits_max + 3];
		scanf("%s", s);
		int k = strlen(s + 2) - j;
		int n = static_cast<int>(strtol(s + 2, NULL, 10));
		int numerator, denominator;
		if (j) {
			numerator = n - n / pow_10s[j];
			denominator = pow_10s[k + j] - pow_10s[k];
		}
		else {
			numerator = n;
			denominator = pow_10s[k];
		}
		int g = gcd(numerator, denominator);
		printf("Case %d: %d/%d\n", case_nr, numerator / g, denominator / g);
	}
	return 0;
}

