
/*
	UVa 665 - False coin

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_665_False_coin.cpp

	An accepted solution.
*/

#include <cstdio>

const int N_max = 100, K_max = 100;

bool lefts[K_max][N_max + 1], rights[K_max][N_max + 1];
int weightings[K_max];

bool is_valid(int K, int ci, int d)
{
	for (int i = 0; i < K; i++) {
		int j = (lefts[i][ci] ? -d : 0) + (rights[i][ci] ? d : 0);
		if (j != weightings[i])
			return false;
	}
	return true;
}

int main()
{
	int M;
	scanf("%d", &M);
	while (M--) {
		int N, K;
		scanf("%d %d", &N, &K);
		for (int i = 0; i < K; i++) {
			for (int j = 1; j <= N; j++)
				lefts[i][j] = rights[i][j] = false;
			int Pi;
			scanf("%d", &Pi);
			for (int j = 0; j < Pi; j++) {
				int k;
				scanf("%d", &k);
				lefts[i][k] = true;
			}
			for (int j = 0; j < Pi; j++) {
				int k;
				scanf("%d", &k);
				rights[i][k] = true;
			}
			char s[2];
			scanf("%s", s);
			if (s[0] == '<')
				weightings[i] = -1;
			else if (s[0] == '>')
				weightings[i] = 1;
			else
				weightings[i] = 0;
		}
		int ci = 0;
		for (int i = 1; i <= N; i++)
			if (is_valid(K, i, 1) || is_valid(K, i, -1)) {
				if (!ci)
					ci = i;
				else {
					ci = 0; break;
				}
			}
		printf("%d\n", ci);
		if (M)
			putchar('\n');
	}
	return 0;
}
