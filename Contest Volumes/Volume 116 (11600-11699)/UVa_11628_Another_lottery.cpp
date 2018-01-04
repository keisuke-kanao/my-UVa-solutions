
/*
	UVa 11628 - Another lottery

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11628_Another_lottery.cpp
*/

#include <cstdio>

const int n_max = 10000;
int tickets[n_max];

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n)
			break;
		int total = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m - 1; j++)
				scanf("%*d");
			scanf("%d", &tickets[i]);
			total += tickets[i];
		}
		for (int i = 0; i < n; i++) {
			int g = gcd(tickets[i], total);
			printf("%d / %d\n", tickets[i] / g, total / g);
		}
	}
	return 0;
}

