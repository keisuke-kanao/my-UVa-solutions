
/*
	UVa 10419 - Sum-up the Primes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10419_Sum-up_the_Primes.cpp
*/

#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int nr_primes = 62, primes[nr_primes] = {
	101, 103, 107, 109,  11, 113, 127,  13, 131, 137,
	139, 149, 151, 157, 163, 167,  17, 173, 179, 181,
	 19, 191, 193, 197, 199,   2, 211, 223, 227, 229,
	 23, 233, 239, 241, 251, 257, 263, 269, 271, 277,
	281, 283,  29, 293,   3,  31,  37,  41,  43,  47,
	  5,  53,  59,  61,  67,   7,  71,  73,  79,  83,
	 89,  97
}; 
const int N_max = 1000, t_max = 14;
bool is_prime[N_max + 1]; // is_prime[i] is true for prime numbers less than 300
bool summed_up[nr_primes][t_max + 1][N_max + 1];
	// summed_up[pi][ti][s] is true if primes[pi] is summed up to s as ti-th number
int sprimes[t_max], isprimes;
int n, t;

bool sum_up_primes(int pi, int ti, int sum)
{ 
	if (sum == n && ti == t)
		return true;
	if (pi >= nr_primes)
		return false;
	if (sum != n && ti == t)
		return false;
	if (sum > n || ti > t)
		return false;
	if (t - ti == 1 && !is_prime[n - sum])
		return false;
	if (summed_up[pi][ti][sum])
		return false;

	summed_up[pi][ti][sum] = true; 
	// add primes[pi] twice
	if (primes[pi] != 2 && ti + 2 <= t &&
		sum_up_primes(pi + 1, ti + 2, sum + 2 * primes[pi])) {
		sprimes[--isprimes] = primes[pi];
		sprimes[--isprimes] = primes[pi];
		return true; 
	}
	// add primes[pi] once
	if (sum_up_primes(pi + 1, ti + 1, sum + primes[pi])) {
		sprimes[--isprimes] = primes[pi];
		return true;
	}
	// not add primes[pi]
	if (sum_up_primes(pi + 1, ti, sum))
		return true;
	return false; 
}

int main() 
{ 
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 0; i < nr_primes; i++)
		is_prime[primes[i]] = true;
	for (int c = 1; ; c++) {
		scanf("%d %d", &n, &t);
		if (!n)
			break;
		printf("CASE %d:\n", c);
		if (t > 1) {
			for (int i = 0; i < nr_primes; i++)
				for (int j = 0; j <= t; j++)
					for (int k = 0; k <= n; k++) 
						summed_up[i][j][k] = false;
			isprimes = t; 
			if (sum_up_primes(0, 0, 0)) { 
				for (int i = 0; i < t; i++)
					printf("%d%c", sprimes[i], ((i < t - 1) ? '+' : '\n'));
			}
			else
				puts("No Solution.");
		}
		else {
			if (is_prime[n])
				printf("%d\n", n);
			else
				puts("No Solution.");
		}
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

