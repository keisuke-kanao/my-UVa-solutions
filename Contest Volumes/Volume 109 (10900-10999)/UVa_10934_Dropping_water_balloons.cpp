
/*
	UVa 10934 - Dropping water balloons

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10934_Dropping_water_balloons.cpp

	This is an accepted solution.
*/

#include <cstdio>

const int k_max = 100, t_max = 64;
unsigned long long dp[k_max + 1][t_max];

int main()
{
    for (int i = 1; i <= k_max; i++)
        for (int j = 1; j < t_max; j++) {
            if(j == 1)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
        }
	while (true) {
		int k;
		unsigned long long n;
		scanf("%d %llu", &k, &n);
		if (!k)
			break;
		int t;
		for (t = 1; t < t_max; t++)
            if(dp[k][t] >= n)
                break;
        if (t < t_max)
			printf("%d\n", t);
        else
			puts("More than 63 trials needed.");
	}
	return 0;
}

