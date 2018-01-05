
/*
	UVa 10532 - Combination! Once Again

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10532_Combination_Once_Again.cpp
*/

/*

dp[i][j] denotes the no. of j combinations possible out of first i numbers.
now the recurrence is..
dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
if(array[i] == array[i-1])
	dp[i][j] -= dp[i-2][j-1];

Now dp[n][r] (for each r) will be the answer.

*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 50;
int nrs[n_max + 1];
unsigned long long combinations[n_max + 1][n_max + 1]; // combinations[i][j] is the number of j combinations out of first i numbers

int main()
{
	for (int cn = 1; ; cn++) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n)
			break;
		for (int i = 1; i <= n; i++)
			scanf("%d", &nrs[i]);
		sort(nrs + 1, nrs + n + 1);
		for (int i = 0; i <= n; i++)
			combinations[i][0] = 1;
		for (int i = 0; i <= n; i++)
			combinations[i][i] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j < i; j++) {
				combinations[i][j] = combinations[i - 1][j - 1] + combinations[i - 1][j];
				if (i > 1 && nrs[i] == nrs[i - 1])
					combinations[i][j] -= combinations[i - 2][j - 1];
			}
		printf("Case %d:\n", cn);
		while (m--) {
			int r;
			scanf("%d", &r);
			printf("%llu\n", combinations[n][r]);
		}
	}
	return 0;
}

/*
#include <stdio.h>

int main() {
    int n, m, x, i, j, k, r, cases = 0;
    while(scanf("%d %d", &n, &m) == 2 && n) {
        int label[150] = {};
        for(i = 0; i < n; i++)
            scanf("%d", &x), label[x]++;
        printf("Case %d:\n", ++cases);
        while(m--) {
            scanf("%d", &r);
            long long dp[100][100] = {};
            dp[0][0] = 1;
            for(i = 1; i <= n; i++) {
                for(j = 0; j <= r; j++)
                    dp[i][j] = dp[i-1][j];
                for(j = 0; j <= r; j++) {
                    for(k = 1; k <= label[i] && j+k <= r; k++) {
                        dp[i][j+k] += dp[i-1][j];
                    }
                }
            }
            printf("%lld\n", dp[n][r]);
        }
    }
    return 0;
}
*/

