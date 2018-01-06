
/*
	UVa 10081 - Tight Words

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10081_Tight_Words.cpp
*/

#include <cstdio>
#include <cmath>

const int k_max = 9, n_max = 100;
double tight_words[n_max][k_max + 1];

int main()
{
	int k, n;
	while (scanf("%d %d", &k, &n) != EOF) {
		for (int i = 0; i <= k; i++)
			tight_words[0][i] = 1.0;
		for (int i = 1; i < n; i++)
			for (int j = 0; j <= k; j++) {
				tight_words[i][j] = tight_words[i - 1][j];
				if (j)
					tight_words[i][j] += tight_words[i - 1][j - 1];
				if (j < k)
					tight_words[i][j] += tight_words[i - 1][j + 1];
			}
			double tw = 0.0;
			for (int i = 0; i <= k; i++)
				tw += tight_words[n - 1][i];
			printf("%.5lf\n", (tw * 100.0) / pow(static_cast<double>(k + 1), static_cast<double>(n)));
	}
	return 0;
}

