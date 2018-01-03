
/*
	UVa 782 - Contour Painting

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_782_Contour_Painting.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_rows_max = 100, nr_columns_max = 100;
char grid[nr_rows_max + 1][nr_columns_max + 1];
bool visited[nr_rows_max][nr_columns_max];

int main()
{
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] = {
		make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)
	};
	int n;
	scanf("%d", &n);
	while (getchar() != '\n')
		;
	while (n--) {
		int nr_rows = 0, sr = -1, sc;
		memset(grid, 0, sizeof(grid));
		while (true) {
			gets(grid[nr_rows]);
			if (grid[nr_rows][0] == '_')
				break;
			for (char* p = grid[nr_rows]; *p; p++)
				if (*p == '*') {
					sr = nr_rows, sc = p - grid[nr_rows];
					*p = '\0';
				}
			nr_rows++;
		}
		memset(visited, 0, sizeof(visited));
		queue< pair<int, int> > q;
		if (sr != -1) {
			visited[sr][sc] = true;
			q.push(make_pair(sr, sc));
		}
		while (!q.empty()) {
			pair<int, int> u = q.front();
			q.pop();
			for (int i = 0; i < nr_dirs; i++) {
				int r = u.first + dirs[i].first, c = u.second + dirs[i].second;
				if (r >= 0 && r < nr_rows && c >= 0 && c < nr_columns_max) {
					if (grid[r][c] != '\0' && grid[r][c] != ' ' && grid[r][c] != '#')
						grid[u.first][u.second] = '#';
					else if (!visited[r][c]) {
						visited[r][c] = true;
						q.push(make_pair(r, c));
					}
				}
			}
		}
		for (int r = 0; r <= nr_rows; r++) {
			for (int c = nr_columns_max - 1, lc = -1; c >= 0; c--) {
				if (grid[r][c] != '\0' && grid[r][c] != ' ') {
					if (lc == -1)
						lc = c; // last column
				}
				else {
					if (lc != -1)
						grid[r][c] = ' ';
					else
						grid[r][c] = '\0';
				}
			}
			puts(grid[r]);
		}
	}
	return 0;
}

