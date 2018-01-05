
/*
	UVa 10617 - Again Palindrome

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10617_Again_Palindrome.cpp
*/

#include <cstdio>
#include <cstring>

const int N_max = 60;
long long nr_ways[N_max][N_max];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		char s[N_max + 1];
		scanf("%s", s);
		int N = strlen(s);
		for (int i = 0; i < N; i++)
			nr_ways[i][i] = 1;
		for (int k = 1; k < N; k++)
			for (int i = 0; i + k < N; i++)
				nr_ways[i][i + k] = nr_ways[i][i + k - 1] + nr_ways[i + 1][i + k] +
					((s[i] == s[i + k]) ? 1 : -nr_ways[i + 1][i + k - 1]);
		printf("%lld\n", nr_ways[0][N - 1]);
	}
	return 0;
}

