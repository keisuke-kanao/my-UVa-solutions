
/*
	UVa 10680 - LCM

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10680_LCM.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

/*
Let's make a table[1000000], then you might find out that if N is not a power of a prime, table[N] would equal to table[N-1], or you have to find out the answer. 
You can do some precalculating to reduce the time to do this. 
And be carefully to the power of 2 and 5, they could make trailing 0's and it would not affect the last non-zero digit.

Process of finding the LCM of two numbers : 

Prime Factorize the two numbers and let 
A = 2^a1 * 3^a2 * 5^a3 * ..... 
B = 2^b1 * 3^b2 * 5^b3 * ..... 

Then the LCM of the two numbers = 
2^max(a1, b1) * 3^max(a2,b2) * 5^max(a3, b3) * ...... 

So if you know the LCM ( for that matter the last digit ) of 1 to N, 
then the last digit of 1 to (N+1) is found by prime factorzing (N+1) and seeing whether any power of prime ( of N + 1) exceeds the previous highest power of the same prime. 
The trick is if (N+1) is a power of prime then only will it make any effect. 

Eg: if N+1 == 8 ( which is a power of prime - 2^3) then you know that there is no number less than 8 that has a prime fact. of 2^3 or more. 
and you also know that 2^2 (3 - 1 = 2) is in the list of 1 to 7.. 
so multiplying the current lcm ( 1 to 7) with 2 will give you the lcm of 
1 -- 8. and so on.. 

btw you have to mod the lcm every time with 1000000 to ensure no overflow occurs... this method took .334 s to get AC.

*/

const int n_max = 1000000, sqrt_n_max = static_cast<int>(sqrt(static_cast<double>(n_max)));
bool not_primes[n_max + 1]; // not_primes[i] is true if i is not a prime
int power_of_primes[n_max + 1];
	// power_of_primes[i] is a positive number p if i is a power of prime number p, otherwise 0
long long lcms[n_max + 1]; // lcms[i] is the last nonzero digit of LCM of 1 to i

void sieve_of_eratosthenes()
{
	not_primes[0] = not_primes[1] = true;
	for (int i = 2; i <= sqrt_n_max; i++)
		if (!not_primes[i]) {
			for (int j = i * i; j <= n_max; j += i)
				not_primes[j] = true;
		}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	sieve_of_eratosthenes();
	for (int i = 2; i <= sqrt_n_max; i++)
		if (!not_primes[i]) {
			for (long long j = static_cast<long long>(i) * i; j <= n_max; j *= i)
				power_of_primes[j] = i;
		}
	lcms[1] = 1; lcms[2] = 2;
	long long l = lcms[2];
	for (int i = 3; i <= n_max; i++) {
		if (!not_primes[i] || power_of_primes[i]) {
			if (!not_primes[i])
				l *= i;
			else
				l *= power_of_primes[i];
			while (!(l % 10))
				l /= 10;
			l %= n_max;
#ifdef DEBUG
			printf("%d: %lld\n", i, l);
#endif
		}
		lcms[i] = l % 10;
	}
#ifdef DEBUG
	printf("%lld\n", lcms[n_max]);
#endif
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		printf("%lld\n", lcms[n]);
	}
	return 0;
}

