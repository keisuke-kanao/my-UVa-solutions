
/*
	UVa 12036 - Stable Grid

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12036_Stable_Grid.cpp
*/

#include <cstdio>
#include <cstring>

const int integers_max = 100;
int freqs[integers_max + 1];
	// freqs[i] is the number of occurrences of i

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n;
		scanf("%d", &n);
		memset(freqs, 0, sizeof(freqs));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				int k;
				scanf("%d", &k);
				freqs[k]++;
			}
		bool yes = true;
		for (int i = 0; i <= integers_max; i++)
			if (freqs[i] > n) {
				yes = false;
				break;
			}
		printf("Case %d: %s\n", t, ((yes) ? "yes" : "no"));
	}
	return 0;
}

