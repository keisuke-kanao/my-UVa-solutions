
/*
	UVa 10097 - The Color Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10097_The_Color_Game.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

const int N_max = 100;

int matrix[N_max + 1][N_max + 1], visited[N_max + 1][N_max + 1];

int main()
{
	for (int g = 1; ; g++) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 1; i <= N; i++)
			for (int j= 1; j <= N; j++) {
				int k;
				scanf("%d", &k);
				matrix[i][j] = k;
				visited[i][j] = -1;
			}
		int N1, N2, N3;
		scanf("%d %d %d", &N1, &N2, &N3);
		int min_moves = -1;
		queue< pair<int, int> > q;
		visited[N1][N2] = 0;
		q.push(make_pair(N1, N2));
		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			N1 = p.first, N2 = p.second;
			int m = visited[N1][N2];
#ifdef DEBUG
			printf("%d %d %d\n", N1, N2, m);
#endif
			if (N1 == N3 || N2 == N3) {
				min_moves = m;
				break;
			}
			if (N1 != N3) {
				if (matrix[N1][N2] && visited[matrix[N1][N2]][N2] == -1) {
#ifdef DEBUG
					printf("  %d %d %d\n", matrix[N1][N2], N2, m + 1);
#endif
					visited[matrix[N1][N2]][N2] = m + 1;
					q.push(make_pair(matrix[N1][N2], N2));
				}
			}
			if (N2 != N3) {
				if (matrix[N2][N1] && visited[matrix[N2][N1]][N1] == -1) {
#ifdef DEBUG
					printf("    %d %d %d\n", matrix[N2][N1], N1, m + 1);
#endif
					visited[matrix[N2][N1]][N1] = m + 1;
					q.push(make_pair(matrix[N2][N1], N1));
				}
			}
		}
		printf("Game #%d\n", g);
		if (min_moves != -1)
			printf("Minimum Number of Moves = %d\n\n", min_moves);
		else
			printf("Destination is Not Reachable !\n\n");
	}
	return 0;
}

