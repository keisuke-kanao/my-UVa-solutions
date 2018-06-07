
/*
	UVa 13185 - DPA Numbers I

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_13185_DPA_Numbers_I.cpp

	This problem is similar to UVa 12043 - Divisors.
*/

#include <cstdio>
#include <cmath>

/*
	for n = p1^e1 * p2^e2 * p3^e3 * ... * pn^en
	number of divisors = (e1 + 1) * (e2 + 1) * (e3 + 1) * ... * (en + 1)
	sum of divisors = ((p1^(e1 + 1) - 1) / (p1 - 1)) * ((p2^(e2 + 1) - 1) / (p2 - 1)) *
		((p3^(e3 + 1) - 1) / (p3 - 1)) * ... * ((pn^(en + 1) - 1) / (pn - 1))
*/

const int n_max = 1000;
int sum_of_proper_divisors[n_max + 1];

void divisors(int n)
{
	int nn = n, e = 0, i, j, sd = 1, p = 1;
	for ( ; !(n & 1); n >>= 1) {
		e++;
		p *= 2;
	}
	if (e) {
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
				sd *= (p * i - 1) / (i - 1);
				e = 0, p = 1;
			}
			i += 2;
		}
	}
	if (e)
		sd *= (p * i - 1) / (i - 1);
	if (n > 1)
		sd *= (n * n - 1) / (n - 1);
	sum_of_proper_divisors[nn] = sd - nn;
}

int main()
{
	for (int i = 1; i <= n_max; i++)
		divisors(i);
#ifdef DEBUG
	for (int i = 1; i <= n_max; i++)
		printf("%d: %d\n", i, sum_of_proper_divisors[i]);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		if (sum_of_proper_divisors[n] < n)
			puts("deficient");
		else if (sum_of_proper_divisors[n] == n)
			puts("perfect");
		else
			puts("abundant");
	}
	return 0;
}

/*
Sample Input
10
5
6
16
18
21
28
29
30
40
43

Sample Output

deficient
perfect
deficient
abundant
deficient
perfect
deficient
abundant
abundant
deficient
*/

