
/*
	UVa 10246 - Asterix and Obelix

	To build using Visucal Studio 2012:
		cl -EHsc UVa_10246_Asterix_and_Obelix.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

const int C_max = 80;
int feasts[C_max + 1];
int fcosts[C_max + 1][C_max + 1], pcosts[C_max + 1][C_max + 1];

void floyd_warshall(int n)
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++) 
			if (pcosts[i][k] != numeric_limits<int>::max())
				for (int j = 1; j <= n; j++)
					if (pcosts[k][j] != numeric_limits<int>::max()) {
	 					if (pcosts[i][k] + pcosts[k][j] + max(fcosts[i][k], fcosts[k][j]) < pcosts[i][j] + fcosts[i][j]) {
							pcosts[i][j] = pcosts[i][k] + pcosts[k][j];
							fcosts[i][j] = max(fcosts[i][k], fcosts[k][j]);
						}
					}
}

int main()
{
	bool printed = false;
	for (int cn = 1; ; cn++) {
		int C, R, Q;
		scanf("%d %d %d", &C, &R, &Q);
		if (!C && !R && !Q)
			break;
		if (printed)
			putchar('\n');
		else
			printed = true;
		for (int i = 1; i <= C; i++)
			scanf("%d", &feasts[i]);
		for (int i = 1; i <= C; i++)
			for (int j = 1; j <= C; j++)
				if (i != j) {
					pcosts[i][j] = numeric_limits<int>::max();
					fcosts[i][j] = 0;
				}
				else {
					pcosts[i][i] = 0;
					fcosts[i][i] = feasts[i];
				}

		while (R--) {
			int c1, c2, d;
			scanf("%d %d %d", &c1, &c2, &d);
			pcosts[c1][c2] = pcosts[c2][c1] = d;
			fcosts[c1][c2] = fcosts[c2][c1] = max(feasts[c1], feasts[c2]);
		}
		floyd_warshall(C);
		floyd_warshall(C);
		printf("Case #%d\n", cn);
		while (Q--) {
			int c1, c2;
			scanf("%d %d", &c1, &c2);
			int min_d = numeric_limits<int>::max();
			printf("%d\n", ((pcosts[c1][c2] != numeric_limits<int>::max()) ? pcosts[c1][c2] + fcosts[c1][c2] : -1));
		}
	}
	return 0;
}

