
/*
	UVa 614 - Mapping the Route

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_614_Mapping_the_Route.cpp

	from ACM North Central Regionals - 1997, Problem 1
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

const int nr_rows_max = 12, nr_columns_max = 12;
int nr_rows, nr_columns;
int walls[nr_rows_max][nr_columns_max];
bool visited[nr_rows_max][nr_columns_max];
pair<int, int> paths[nr_rows_max][nr_columns_max];
int cells[nr_rows_max][nr_columns_max];

bool dfs(const pair<int, int>& u, const pair<int, int>& g)
{
	const int nr_dirs = 4;
	pair<int, int> dirs[nr_dirs] = {make_pair(0, -1), make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0)};

#ifdef DEBUG
	printf("%d %d\n", u.first, u.second);
#endif
	visited[u.first][u.second] = true;
	if (u == g)
		return true;
	for (int i = 0; i < nr_dirs; i++) {
		int r = u.first + dirs[i].first, c = u.second + dirs[i].second;
		if (r < 0 || r >= nr_rows || c < 0 || c >= nr_columns)
			continue;
		if (i == 0 && walls[r][c] & 1 || i == 2 && walls[r][c - 1] & 1 || // eastern wall
			i == 1 && walls[r][c] & 2 || i == 3 && walls[r - 1][c] & 2) // southern wall
			continue;
		if (!visited[r][c]) {
			paths[r][c] = u;
			if (dfs(make_pair(r, c), g))
				return true;
		}
	}
	return false;
}

int follow_paths(const pair<int, int>& s, const pair<int, int>& u)
{
	if (u == s)
		return cells[u.first][u.second] = 1;
	else
		return cells[u.first][u.second] = follow_paths(s, paths[u.first][u.second]) + 1;
}

int main()
{
	for (int maze_nr = 1; ; maze_nr++) {
		pair<int, int> s, g;
		scanf("%d %d %d %d %d %d", &nr_rows, &nr_columns, &s.first, &s.second, &g.first, &g.second);
		s.first--; s.second--; g.first--; g.second--;
		if (!nr_rows)
			break;
		for (int r = 0; r < nr_rows; r++)
			for (int c = 0; c < nr_columns; c++)
				scanf("%d", &walls[r][c]);

		memset(visited, 0, sizeof(visited));
		memset(cells, 0, sizeof(cells));
		if (dfs(s, g))
			follow_paths(s, g);
		for (int r = 0; r < nr_rows; r++)
			for (int c = 0; c < nr_columns; c++)
				if (visited[r][c] && !cells[r][c])
					cells[r][c] = -1;
		printf("Maze %d\n\n", maze_nr);
		putchar('+');
		for (int c = 0; c < nr_columns; c++)
			printf("---+");
		putchar('\n');
		for (int r = 0; r < nr_rows; r++) {
			putchar('|');
			for (int c = 0; c < nr_columns; c++) {
				if (cells[r][c] > 0)
					printf("%3d", cells[r][c]);
				else if (cells[r][c] < 0)
					printf("???");
				else
					printf("   ");
				putchar((walls[r][c] & 1 || c == nr_columns - 1) ? '|' : ' ');
			}
			putchar('\n');
			if (r < nr_rows - 1) {
				putchar('+');
				for (int c = 0; c < nr_columns; c++)
					if (walls[r][c] & 2)
						printf("---+");
					else
						printf("   +");
				printf("\n");
			}
		}
		putchar('+');
		for (int c = 0; c < nr_columns; c++)
			printf("---+");
		printf("\n\n\n");
	}
	return 0;
}

