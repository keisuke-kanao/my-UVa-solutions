
/*
	UVa 13131 - Divisors

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_13131_Divisors.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

int sum_of_divisors(int n, int k)
{
	int s = 0;
	for (int i = 1, ie = static_cast<int>(sqrt(n)); i <= ie; i++)
		if (!(n % i)) {
			if (i % k)
				s += i;
			int j = n / i;
			if (i != j && j % k)
				s += j;
		}
	return s;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, K;
		scanf("%d %d", &N, &K);
		printf("%d\n", (K != 1) ? sum_of_divisors(N, K) : 0);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

