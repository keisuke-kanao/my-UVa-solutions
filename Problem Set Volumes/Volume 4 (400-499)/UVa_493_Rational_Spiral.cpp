
/*
	UVa 493 - Rational Spiral

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_493_Rational_Spiral.cpp
*/

#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int n_max = 650, nr_rationals_max = 514407;
int coprimes[n_max];

struct rational {
	int numerator_, denominator_;
} rationals[nr_rationals_max] = {
	{1, 1}, {0, 1}, {-1, 1}
};
int nr_rationals = 3;

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 2; i <= n_max; i++) {
		int nr_coprimes = 0;
		for (int j = 1; j < i; j++)
			if (gcd(i, j) == 1)
				coprimes[nr_coprimes++] = j;
		for (int j = nr_coprimes - 1; j >= 0; j--, nr_rationals++)
			rationals[nr_rationals].numerator_ = -i, rationals[nr_rationals].denominator_ = coprimes[j];
		for (int j = 0; j < nr_coprimes; j++, nr_rationals++)
			rationals[nr_rationals].numerator_ = i, rationals[nr_rationals].denominator_ = coprimes[j];
		for (int j = nr_coprimes - 1; j >= 0; j--, nr_rationals++)
			rationals[nr_rationals].numerator_ = coprimes[j], rationals[nr_rationals].denominator_ = i;
		for (int j = 0; j < nr_coprimes; j++, nr_rationals++)
			rationals[nr_rationals].numerator_ = -coprimes[j], rationals[nr_rationals].denominator_ = i;
	}
#ifdef DEBUG
	printf("%d\n", nr_rationals);
#endif
	int i;
	while (scanf("%d", &i) != EOF)
		printf("%d / %d\n", rationals[i].numerator_, rationals[i].denominator_);
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

