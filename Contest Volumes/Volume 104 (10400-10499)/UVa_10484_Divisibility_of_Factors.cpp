
/*
	UVa 10484 - Divisibility of Factors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10484_Divisibility_of_Factors.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

const int N_max = 100;
int exps[N_max + 1];

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

bool divisibility_of_factors(int n)
{
	int i, j, e = 0;
	for ( ; !(n & 1); n >>= 1)
		e++;
	if (e) {
		if (exps[2] < e)
			return false;
		exps[2] -= e;
		e = 0;
	}
	for (i = 3, j = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); i <= j; ) {
		if (!(n % i)) {
			e++;
			n /= i;
		}
		else {
			if (e) {
				if (i > N_max || exps[i] < e)
					return false;
				exps[i] -= e;
				e = 0;
			}
			i += 2;
		}
	}
	if (e) {
		if (i > N_max || exps[i] < e)
			return false;
		exps[i] -= e;
	}
	if (n > 1) {
		if (n > N_max || !exps[n])
			return false;
		exps[n]--;
	}
	return true;
}

int main()
{
	while (true) {
		int N, D;
		scanf("%d %d", &N, &D);
		if (!N && !D)
			break;
		memset(exps, 0, sizeof(exps));
		for (int i = N; i > 1; i--)
			divisors(i);
		long long nr = 1;
		if (divisibility_of_factors(abs(D))) {
			for (int i = 2; i <= N; i++)
				if (exps[i])
					nr *= exps[i] + 1;
		}
		else
			nr = 0;
		printf("%lld\n", nr);
	}
	return 0;
}

/*
Sample Input

10 2
9 3
0 0

Sample Output

240
128

*/

