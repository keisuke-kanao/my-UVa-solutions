
/*
	UVa 11424 - GCD - Extreme (I)

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11424_GCD_Extreme_I.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int N_max = 200000;
int phis[N_max + 1];
long long gs[N_max + 1];

/*
	For sum of GCD, refer to Pillai's arithmetical function.
		(http://en.wikipedia.org/wiki/Pillai%27s_arithmetical_function)

	Another idea for caluculating the Pillai's arithmetical function:
		Calculate the Pillai's arithmetical function from 1 to upwards processing like Sieve of Eratosthenes.
*/

int phi_function(int n)
{
	if (phis[n])
		return phis[n];
	int m = n, result = n;
	for (int i = 2, j = static_cast<int>(sqrt(static_cast<double>(n))); i <= j; i++) {
		if (!(n % i)) {
			result -= result / i;
			do
				n /= i; 
			while (!(n % i));
		}
	}
	if (n > 1)
		result -= result / n;
	return phis[m] = result;
}

long long pillai_function(int n)
{
	long long pillai = 0;
	for (int i = 1, j = static_cast<int>(sqrt(static_cast<double>(n))); i <= j; i++)
		if (!(n % i)) {
			pillai += i * phi_function(n / i);
			if (i < n / i)
				pillai += (n / i) * phi_function(i);
		}
	return pillai;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	gs[1] = 0;
	for (int i = 2; i <= N_max; i++)
		gs[i] = gs[i - 1] + pillai_function(i) - i;
#ifdef DEBUG
	printf("%lld\n", gs[N_max]);
#endif
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		printf("%lld\n", gs[N]);
	}
	return 0;
}

