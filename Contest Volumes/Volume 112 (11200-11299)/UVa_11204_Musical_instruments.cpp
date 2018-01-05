
/*
	UVa 11204 - Musical instruments

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11204_Musical_instruments.cpp
*/

#include <cstdio>

const int N_max = 32, M_max = 32;
int priorities[M_max][N_max];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int N, M;
		scanf("%d %d", &N, &M);
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &priorities[i][j]);
		int nr_distributions = 1;
		for (int j = 0; j < N; j++) {
			int nr = 0;
			for (int i = 0; i < M; i++)
				if (priorities[i][j] == 1)
					nr++;
			if (nr)
				nr_distributions *= nr;
		}
		printf("%d\n", nr_distributions);
	}
	return 0;
}

