
/*
	UVa 11532 - Simple Adjacency Maximization

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11532_Simple_Adjacency_Maximization.cpp

	An accepted solution.
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	const int bs_max = 50;
	int C, P, Q;
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &P, &Q);
		int p = 0, q = 0;
		unsigned long long l = 0, b = 1;
		if (p < P) {
			p++;
			l |= b;
			b <<= 1;
		}
		if (q < Q) {
			q++;
			b <<= 1;
		}
		while (p < P || q < Q) {
			if (p < P) {
				p++;
				l |= b;
				b <<= 1;
			}
			if (p < P) {
				p++;
				l |= b;
				b <<= 1;
			}
			if (q < Q) {
				q++;
				b <<= 1;
			}
		}
		b >>= 1;
		unsigned long long rl = 0, rb = 1;
		for (int i = P + Q - 1; i >= 0; i--, b >>= 1, rb <<= 1)
			if (l & b)
				rl |= rb;
		printf("%llu\n", min(l, rl));
	}
	return 0;
}

