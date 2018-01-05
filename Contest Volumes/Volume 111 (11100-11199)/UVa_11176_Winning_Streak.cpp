
/*
	UVa 11176 - Winning Streak

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_11176_Winning_Streak.cpp
*/

#include <cstdio>
#include <cstring>
#include <cmath>

const int n_max = 500;

double probabilities[n_max + 1][n_max + 1];
	// probabilities[i][j] is the probability of having at most j consecutive wins in i consecutive games
	// The probability of having a winning streak of length j is (probabilities[n][j] - probabilities[n][j - 1]).

int main()
{
	while (true) {
		int n;
		double p;
		scanf("%d %lf", &n, &p);
		if (!n)
			break;
		memset(probabilities, 0, sizeof(probabilities));
		for (int i = 0; i <= n; i++) {
			if (i >= 1)
				probabilities[i][i - 1] = 1 - pow(p, static_cast<double>(i));
			if (i >= 2)
				for (int j = 0; j <= i - 2; j++)
					probabilities[i][j] = probabilities[i - 1][j] -
						pow(p, static_cast<double>(j + 1)) * (1 - p) * probabilities[i - 2 - j][j];
			for (int j = i; j <= n; j++)
				probabilities[i][j] = 1.0;
		}
		double lws = 0.0; // longest winning streak
		for (int j = 1; j <= n; j++)
			lws += (probabilities[n][j] - probabilities[n][j - 1]) * j;
		printf("%lf\n", lws);
	}
	return 0;
}

