
/*
	UVa 11679 - Sub-prime

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11679_Sub_prime.cpp
*/

#include <cstdio>

int main()
{
	while (true) {
		int b, n;
		scanf("%d %d", &b, &n);
		if (!b && !n)
			break;
		const int b_max = 20;
		int banks[b_max + 1];
		for (int i = 1; i <= b; i++)
			scanf("%d", &banks[i]);
		while (n--) {
			int d, c, v;
			scanf("%d %d %d", &d, &c, &v);
			banks[d] -= v;
			banks[c] += v;
		}
		bool possible = true;
		for (int i = 1; i <= b; i++)
			if (banks[i] < 0) {
				possible = false;
				break;
			}
		puts((possible) ? "S" : "N");
	}
	return 0;
}

