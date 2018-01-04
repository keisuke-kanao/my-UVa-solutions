
/*
	UVa 474 - Heads / Tails Probability

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_474_Heads_Tails_Probability.cpp
*/

#include <cstdio>
using namespace std;

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		double p = 1.0;
		int exponent = 0;
		for (int i = 1; i <= n; i++) {
			p /= 2.0;
			if (p < 1.0) {
				p *= 10.0;
				exponent++;
			}
		}
		printf("2^%d = %.3lfe-%d\n", -n, p, exponent);
	}
	return 0;
}

