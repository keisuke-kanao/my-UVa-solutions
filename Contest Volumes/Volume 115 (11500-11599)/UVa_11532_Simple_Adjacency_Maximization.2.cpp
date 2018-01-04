
/*
	UVa 11532 - Simple Adjacency Maximization

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11532_Simple_Adjacency_Maximization.cpp

	Another accepted solution.
*/

#include <algorithm>
#include <bitset>
#include <cstdio>
using namespace std;

int main()
{
	const int bs_max = 50;
	int C, P, Q;
	scanf("%d", &C);
	while (C--) {
		scanf("%d %d", &P, &Q);
		bitset<bs_max> bs;
		int p = 0, q = 0, i = 0;
		if (p < P)
			bs.set(i++), p++;
		if (q < Q)
			i++, q++;
		while (p < P || q < Q) {
			if (p < P)
				bs.set(i++), p++;
			if (p < P)
				bs.set(i++), p++;
			if (q < Q)
				i++, q++;
		}
#ifdef DEBUG
		puts(bs.to_string().c_str());
#endif
		unsigned long long l = bs.to_ullong();
		unsigned long long rl = 0, b = 1;
		for (i = P + Q - 1; i >= 0; i--, b <<= 1)
			if (bs.test(i))
				rl += b;
		printf("%llu\n", min(l, rl));
	}
	return 0;
}

