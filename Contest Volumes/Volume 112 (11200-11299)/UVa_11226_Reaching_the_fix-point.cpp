
/*
	UVa 11226 - Reaching the fix-point.

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11226_Reaching_the_fix-point.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int n_max = 500000;
int lsopfs[n_max + 1]; // lsopfs[i] is the number of calls of sopf() for i to reach the fix-point

int sopf(int n) // sum of prime factors of n
{
	int s = 0;
	for ( ; !(n & 1); n >>= 1)
		s += 2;
	for (int i = 3, e = static_cast<int>(ceil(sqrt(static_cast<double>(n)))); i <= e; ) {
		if (!(n % i)) {
			n /= i;
			s += i;
		}
		else
			i += 2;
	}
	if (n > 1)
		s += n;
	return s;
}

int main()
{
	for (int i = 2; i <= n_max; i++) {
		int j, ps = i, s;
		for (j = 1; ; j++, ps = s) {
			if ((s = sopf(ps)) == ps) {
				lsopfs[i] = j;
				break;
			}
			else if (lsopfs[s]) {
				lsopfs[i] = lsopfs[s] + 1;
				break;
			}
		}
	}
#ifdef DEBUG
	printf("%d\n", lsopfs[n_max]);
#endif
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (n > m)
			swap(n, m);
		int max_lsopf = 0;
		for ( ; n <= m; n++)
			if (lsopfs[n] > max_lsopf)
				max_lsopf = lsopfs[n];
		printf("Case #%d:\n%d\n", t, max_lsopf);
	}
	return 0;
}

