
/*
	UVa 12043 - Divisors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12043_Divisors.cpp
*/

#include <cstdio>
#include <cmath>

/*
	for n = p1^e1 * p2^e2 * p3^e3 * ... * pn^en
	number of divisors = (e1 + 1) * (e2 + 1) * (e3 + 1) * ... * (en + 1)
	sum of divisors = ((p1^(e1 + 1) - 1) / (p1 - 1)) * ((p2^(e2 + 1) - 1) / (p2 - 1)) *
		((p3^(e3 + 1) - 1) / (p3 - 1)) * ... * ((pn^(en + 1) - 1) / (pn - 1))
*/

const int n_max = 100000;
int number_of_divisors[n_max + 1], sum_of_divisors[n_max + 1];
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

void divisors(int n)
{
	int nn = n, nd = 1, e = 0, i, j;
	long long sd = 1, p = 1;
	for ( ; !(n & 1); n >>= 1) {
		e++;
		p *= 2;
	}
	if (e) {
		nd *= e + 1;
		sd *= p * 2 - 1;
		e = 0, p = 1;
	}
	for (i = 3, j = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); i <= j; ) {
		if (!(n % i)) {
			e++;
			p *= i;
			n /= i;
		}
		else {
			if (e) {
				nd *= e + 1;
				sd *= (p * i - 1) / (i - 1);
				e = 0, p = 1;
			}
			i += 2;
		}
	}
	if (e) {
		nd *= e + 1;
		sd *= (p * i - 1) / (i - 1);
	}
	if (n > 1) {
		nd *= 2;
		sd *= (static_cast<long long>(n) * n - 1) / (n - 1);
	}
	number_of_divisors[nn] = nd;
	sum_of_divisors[nn] = sd;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 1; i <= n_max; i++)
		divisors(i);
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
#ifdef DEBUG
	for (int i = 1; i <= n_max; i++)
		printf("%d: %d %lld\n", i, number_of_divisors[i], sum_of_divisors[i]);
#endif
	int T;
	scanf("%d", &T);
	while (T--) {
		int a, b, k;
		scanf("%d %d %d", &a, &b, &k);
		int snd = 0;
		long long ssd = 0;
		for ( ; a <= b; a++)
			if (!(a % k)) {
				snd += number_of_divisors[a];
				ssd += sum_of_divisors[a];
			}
		printf("%d %lld\n", snd, ssd);
	}
	return 0;
}

