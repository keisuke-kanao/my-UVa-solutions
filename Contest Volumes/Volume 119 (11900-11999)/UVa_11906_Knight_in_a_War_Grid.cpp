
/*
	UVa 11906 - Knight in a War Grid

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11906_Knight_in_a_War_Grid.cpp
*/

#include <cstdio>

const int R_max = 100, C_max = 100;

int R, C, M, N;
bool visited[R_max][C_max];
int grid[R_max][C_max];
	// grid[r][c] is the number of squares from which the knight can reach grid[r][c]
	// -1 for the ones that the knight cannot reach, -2 for the ones containing water

void dfs(int r, int c)
{
	visited[r][c] = true;
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
	int ctr = 0;
	if (!M) {
		for (int i = 0; i < nr_dirs / 2; i++) {
			int nr = r + N * dirs[i][0];
			if (nr >= 0 && nr < R && grid[nr][c] != -2) {
				ctr++;
				if (!visited[nr][c])
					dfs(nr, c);
			}
		}
		for (int i = 0; i < nr_dirs / 2; i++) {
			int nc = c + N * dirs[i][0];
			if (nc >= 0 && nc < C && grid[r][nc] != -2) {
				ctr++;
				if (!visited[r][nc])
					dfs(r, nc);
			}
		}
	}
	else if (!N) {
		for (int i = 0; i < nr_dirs / 2; i++) {
			int nr = r + M * dirs[i][0];
			if (nr >= 0 && nr < R && grid[nr][c] != -2) {
				ctr++;
				if (!visited[nr][c])
					dfs(nr, c);
			}
		}
		for (int i = 0; i < nr_dirs / 2; i++) {
			int nc = c + M * dirs[i][0];
			if (nc >= 0 && nc < C && grid[r][nc] != -2) {
				ctr++;
				if (!visited[r][nc])
					dfs(r, nc);
			}
		}
	}
	else {
		for (int i = 0; i < nr_dirs; i++) {
			int nr = r + M * dirs[i][0], nc = c + N * dirs[i][1];
			if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != -2) {
				ctr++;
				if (!visited[nr][nc])
					dfs(nr, nc);
			}
		}
		if (M != N)
			for (int i = 0; i < nr_dirs; i++) {
				int nr = r + N * dirs[i][0], nc = c + M * dirs[i][1];
				if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != -2) {
					ctr++;
					if (!visited[nr][nc])
						dfs(nr, nc);
				}
			}
	}
	grid[r][c] = ctr;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int W;
		scanf("%d %d %d %d %d", &R, &C, &M, &N, &W);
		for (int r = 0; r < R; r++)
			for (int c = 0; c < C; c++) {
				visited[r][c] = false;
				grid[r][c] = -1;
			}
		while (W--) {
			int r, c;
			scanf("%d %d", &r, &c);
			grid[r][c] = -2;
		}
		dfs(0, 0);
		int even = 0, odd = 0;
		for (int r = 0; r < R; r++)
			for (int c = 0; c < C; c++)
				if (grid[r][c] >= 0) {
					if (grid[r][c] & 1)
						odd++;
					else
						even++;
				}
		printf("Case %d: %d %d\n", t, even, odd);
	}
	return 0;
}

