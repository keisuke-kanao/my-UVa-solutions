/*
	UVa 1600 - Patrol Robot

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_1600_Patrol_Robot.cpp
*/

#include <queue>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int m_max = 20, n_max = 20, k_max = 20;

const int nr_dirs = 4;
const int dirs[nr_dirs][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int obstacles[m_max][n_max]; // obstacles[i][j] is 1 if there is an obstacle at cell(i, j), 0 otherwise
int nr_moves[m_max][n_max][k_max + 1];
	// nr_moves[i][j][k] is the minimum number of moves from (0, 0) to (i, j) with the turbo mode used for k cells

struct path {
	int i_, j_, k_, nr_;
	path(int i, int j, int k, int nr) : i_(i), j_(j), k_(k), nr_(nr) {}
};

int main()
{
	int ns;
	scanf("%d", &ns);
	while (ns--) {
		int m, n, k;
		scanf("%d %d", &m, &n);
		scanf("%d", &k);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				scanf("%d", &obstacles[i][j]);
				for (int l = 0; l <= k; l++)
					nr_moves[i][j][l] = infinite;
			}
		queue<path> q;
		nr_moves[0][0][0] = 0;
		q.push(path(0, 0, 0, nr_moves[0][0][0]));
		while (!q.empty()) {
			path p = q.front(); q.pop();
#ifdef DEBUG
			printf("[%d][%d][%d]: %d\n", p.i_, p.j_, p.k_, p.nr_);
#endif
			for (int d = 0; d < nr_dirs; d++) {
				int i = p.i_ + dirs[d][0], j = p.j_ + dirs[d][1], l = p.k_;
				if (i < 0 || i >= m || j < 0 || j >= n)
					continue;
				if (obstacles[i][j]) {
					if (l + 1 <= k && p.nr_ + 1 < nr_moves[i][j][l + 1]) {
						nr_moves[i][j][l + 1] = p.nr_ + 1;
						q.push(path(i, j, l + 1, nr_moves[i][j][l + 1]));
					}
				}
				else {
					if (p.nr_ + 1 < nr_moves[i][j][0]) {
						nr_moves[i][j][0] = p.nr_ + 1;
						q.push(path(i, j, 0, nr_moves[i][j][0]));
					}
				}
			}
		}
		int nr = infinite;
		for (int l = 0; l <= k; l++)
			if (nr_moves[m - 1][n - 1][l] < nr)
				nr = nr_moves[m - 1][n - 1][l];
		printf("%d\n", (nr < infinite) ? nr : -1);
	}
	return 0;
}

