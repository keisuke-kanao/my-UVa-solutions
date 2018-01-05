
/*
	UVa 11347 - Multifactorials

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11347_Multifactorials.cpp
*/

#include <cstdio>
#include <cstring>
#include <cmath>

const int n_max = 1000, k_max = 20;
const long long infinity = 1000000000000000000;
int exps[n_max + 1];

void divisors(int n)
{
	int i, j, e = 0;
	for ( ; !(n & 1); n >>= 1)
		e++;
	if (e) {
		exps[2] += e;
		e = 0;
	}
	for (i = 3, j = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); i <= j; ) {
		if (!(n % i)) {
			e++;
			n /= i;
		}
		else {
			if (e) {
				exps[i] += e;
				e = 0;
			}
			i += 2;
		}
	}
	if (e)
		exps[i] += e;
	if (n > 1)
		exps[n] += 1;
}

int main()
{
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int n;
		char s[k_max + 1];
		scanf("%d%s", &n, s);
		int k = strlen(s);
		for (int i = 2; i <= n; i++)
			exps[i] = 0;
		for (int i = n; i > 1; i -= k)
			divisors(i);
		long long nr = 1;
		for (int i = 2; i <= n; i++)
			if (exps[i] && (nr *= exps[i] + 1) > infinity) {
				nr = 0;
				break;
			}
		printf("Case %d: ", cn);
		if (nr)
			printf("%lld\n", nr);
		else
			puts("Infinity");
	}
	return 0;
}

