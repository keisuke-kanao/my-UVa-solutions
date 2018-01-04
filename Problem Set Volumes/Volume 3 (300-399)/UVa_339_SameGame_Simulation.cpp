
/*
	UVa 339 - SameGame Simulation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_339_SameGame_Simulation.cpp

	from ACM North Central Regionals 1995
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1995/index.html)
*/

#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

const int M_max = 10, N_max = 40;

int M, N, grid[M_max][N_max];

#ifdef DEBUG
void print_grid()
{
	putchar('\n');
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			printf("%c%c", ((grid[i][j] >= 0) ? grid[i][j] + '0' : ' '),
				((j < N - 1) ? ' ' : '\n'));
}
#endif

bool mark_removed_cells(int sr, int sc)
{
	if (grid[sr][sc] == -1)
		return false;
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] = {make_pair(-1, 0), make_pair(1, 0), make_pair(0, 1), make_pair(0, -1)};
	int nr_removed = 0, v = grid[sr][sc];
	queue< pair<int, int> > q;
	grid[sr][sc] = -1;
	q.push(make_pair(sr, sc));
	while (!q.empty()) {
		pair<int, int> i = q.front();
		q.pop();
		for (int j = 0; j < nr_dirs; j++) {
			int r = i.first + dirs[j].first, c = i.second + dirs[j].second;
			if (r >= 0 && r < M && c >= 0 && c < N && grid[r][c] == v) {
				grid[r][c] = -1;
				nr_removed++;
				q.push(make_pair(r, c));
			}
		}
	}
	if (nr_removed)
		return true;
	else {
		grid[sr][sc] = v;
		return false;
	}
}

bool remove_cells()
{
	for (int j = 0; j < N; j++) { // remove cells for each column
		for (int i = 0, k = 1; k < M; ) {
			if (grid[i][j] >= 0) {
				if (++i == k)
					k++;
			}
			else {
				for ( ; k < M; k++)
					if (grid[k][j] >= 0)
						break;
				if (k < M) {
					grid[i][j] = grid[k][j];
					grid[k][j] = -1;
					i++; k++;
				}
			}
		}
	}
	for (int j = 0, k = 1; k < N; ) { // remove columns
		if (grid[0][j] >= 0) {
			if (++j == k)
				k++;
		}
		else {
			for ( ; k < N; k++)
				if (grid[0][k] >= 0)
					break;
			if (k < N) {
				for (int i = 0; i < M; i++) {
					grid[i][j] = grid[i][k];
					grid[i][k] = -1;
				}
				j++; k++;
			}
		}
	}
#ifdef DEBUG
	print_grid();
#endif
	return grid[0][0] == -1;
}

int main()
{
	for (int g = 1; ; g++) {
		scanf("%d %d", &M, &N);
		if (!M && !N)
			break;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &grid[i][j]);
		bool won = false;
		while (true) {
			int r, c;
			scanf("%d %d", &r, &c);
			if (!r && !c)
				break;
			if (!won) {
				r--; c--;
				if (r >= 0 && r < M && c >= 0 && c < N &&
					mark_removed_cells(r, c)) // mark the cells of a connected region as removed
					won = remove_cells();
			}
		}
		printf("Grid %d.\n", g);
		if (won)
			puts("    Game Won");
		else {
			for (int i = M - 1; i >= 0; i--) {
				printf("    ");
				for (int j = 0; j < N; j++)
					printf("%c ", (grid[i][j] >= 0) ? grid[i][j] + '0' : ' ');
				putchar('\n');
			}
		}
		putchar('\n');
	}
	return 0;
}

