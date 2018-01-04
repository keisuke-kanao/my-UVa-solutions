
/*
	UVa 12455 - Bars

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12455_Bars.cpp
*/

#include <cstdio>

const int p_max = 20;
int bars[p_max];
int sums[p_max]; // sums[i] is the sum of bar lengths from i-th bar to the last bar

bool put_bars_together(int p, int pi, int n, int b)
{
	if (b == n)
		return true;
	else if (b < n && pi < p && b + sums[pi] >= n) {
		if (put_bars_together(p, pi + 1, n, b + bars[pi]))
			return true;
		return put_bars_together(p, pi + 1, n, b);
	}
	else
		return false;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, p;
		scanf("%d%d", &n, &p);
		for (int i = 0; i < p; i++)
			scanf("%d", &bars[i]);
		for (int i = p - 1, s = 0; i >= 0; i--) {
			s += bars[i];
			sums[i] = s;
		}
		puts((put_bars_together(p, 0, n, 0)) ? "YES" : "NO");
	}
	return 0;
}

