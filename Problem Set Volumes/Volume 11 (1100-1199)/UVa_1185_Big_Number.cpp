
/*
	UVa 1185 - Big Number

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1185_Big_Number.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int n_max = 10000000;
int nr_digits[n_max + 1];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	nr_digits[0] = 1;
	double s = 0.0;
	for (int i = 1; i <= n_max; i++) {
		s += log10(static_cast<double>(i));
		nr_digits[i] = static_cast<int>(s + 1.0);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
#ifdef DEBUG
	printf("%d\n", nr_digits[n_max]);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", nr_digits[n]);
	}
	return 0;
}

