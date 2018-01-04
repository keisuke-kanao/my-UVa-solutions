
/*
	UVa 11426 - GCD - Extreme (II)

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11426_GCD_Extreme_II.cpps
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int N_max = 4000000;
int phis[N_max + 1];
long long gs[N_max + 1];

/*
For sum of GCD, refer to Pillai's arithmetical function.
	(http://en.wikipedia.org/wiki/Pillai%27s_arithmetical_function)
*/

/*
long long pillai_function(int n)
{
	long long pillai = 0;
	for (int i = 1, j = static_cast<int>(sqrt(static_cast<double>(n))); i <= j; i++)
		if (!(n % i)) {
			pillai += i * phis[n / i];
			if (i < n / i)
				pillai += (n / i) * phis[i];
		}
	return pillai;
}
*/

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	// calculate the Euler's totient or phi function from 1 to upwards, processing like Sieve of Eratosthenes
	phis[1] = 1;
	for (int i = 2; i <= N_max; i++)
		if (!phis[i]) {
			phis[i] = i - 1;
			for (int j = i + i; j <= N_max; j += i) {
				if (!phis[j])
					phis[j] = j;
				phis[j] /= i; phis[j] *= i - 1;
			}
		}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	for (int i = 1; i <= N_max; i++)
		for (int j = i + i; j <= N_max; j += i)
			gs[j] += i * phis[j / i]; // calculate sum of GCD(j, k), k = 1, 2, ..., (j - 1), i.e., (pillai_function(j) - j)
	for (int i = 1; i <= N_max; i++)
		gs[i] += gs[i - 1];
/*
	gs[1] = 0;
	for (int i = 2; i <= N_max; i++)
		gs[i] = gs[i - 1] + pillai_function(i) - i;
*/
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

