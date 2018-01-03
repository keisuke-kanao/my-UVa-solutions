
/*
	UVa 890 - Maze (II)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_890_Maze_II.cpp
*/

#include <algorithm>
#include <utility>
#include <cstdio>
using namespace std;

const int M_max = 39, N_max = 39;

int M, N, nr_cells;
char maze[M_max + 1][2 * (N_max + 1)];
bool visited[M_max + 1][N_max + 1];
pair<int, int> cells[M_max * N_max];

inline bool unvisited(int r, int c)
{
	return r >= 0 && r < M && c >= 0 && c < N && !visited[r][c];
}

inline void add_cell(int r, int c)
{
	visited[r][c] = true;
	cells[nr_cells++] = make_pair(r, c);
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &M, &N);
		for (int i = 0; i <= M; i++) {
			int j, k = (i) ? 2 * N : 2 * N - 1;
			for (j = 0; j <= k; j++) {
				if (j & 1)
					maze[i][j] = '_';
				else if (i)
					maze[i][j] = '|';
				else
					maze[i][j] = ' ';
			}
			maze[i][j] = '\0';
		}
#ifdef DEBUG
		for (int i = 0; i <= M; i++)
			puts(maze[i]);
#endif
		nr_cells = 0;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				visited[i][j] = false;
		int r, c;
		scanf("%d %d", &r, &c);
		r = M - r, c--;
		add_cell(r, c);
		while (true) {
			for ( ; nr_cells; nr_cells--) {
				const pair<int, int>& cell = cells[nr_cells - 1];
				if (unvisited(cell.first - 1, cell.second) || unvisited(cell.first + 1, cell.second) ||
					unvisited(cell.first, cell.second - 1) || unvisited(cell.first, cell.second + 1))
					break;
			}
			if (!nr_cells)
				break;
			const pair<int, int>& cell = cells[nr_cells - 1];
			char command[2];
			scanf("%s", command);
			switch (command[0]) {
			case 'F':
			{
				int n;
				scanf("%d", &n);
				reverse(cells + (n - 1), cells + nr_cells);
			}
				break;
			case 'U':
				r = cell.first - 1, c = cell.second;
				maze[r + 1][c * 2 + 1] = ' ';
				add_cell(r, c);
				break;
			case 'D':
				r = cell.first + 1, c = cell.second;
				maze[r][c * 2 + 1] = ' ';
				add_cell(r, c);
				break;
			case 'L':
				r = cell.first, c = cell.second - 1;
				maze[r + 1][(c + 1) * 2] = ' ';
				add_cell(r, c);
				break;
			case 'R':
				r = cell.first, c = cell.second + 1;
				maze[r + 1][c * 2] = ' ';
				add_cell(r, c);
				break;
			}
#ifdef DEBUG
			for (int i = 0; i <= M; i++)
				puts(maze[i]);
#endif
		}
		for (int i = 0; i <= M; i++)
			puts(maze[i]);
		putchar('\n');
	}
	return 0;
}

