
/*
	UVa 785 - Grid Colouring

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_785_Grid_Colouring.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_lines_max = 64 /* actually, 31 */, nr_chars_max = 128 /* actually, 80 */;
char grid[nr_lines_max + 1][nr_chars_max + 1];
int nr_columns[nr_lines_max + 1];
bool visited[nr_lines_max + 1][nr_chars_max + 1];
const int nr_dirs = 4;
const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool is_zone(int nr_rows, int i, int j)
{
	memset(visited, 0, sizeof(visited));
	char mc = grid[i][j];
	queue< pair<int, int> > q;
	visited[i][j] = true;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front(); q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			int r = p.first + dirs[i][0], c = p.second + dirs[i][1];
			if (r < 0 || r >= nr_rows || c < 0 || c >= nr_columns[r])
				return false; // a zone is not enclosed or a counter
			else if ((grid[r][c] == ' ' || grid[r][c] == mc) && !visited[r][c]) {
				visited[r][c] = true;
				q.push(make_pair(r, c));
			}
		}
	}
	return true;
}

bool mark_zone(int nr_rows, int i, int j)
{
	char mc = grid[i][j];
	queue< pair<int, int> > q;
	visited[i][j] = true;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front(); q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			int r = p.first + dirs[i][0], c = p.second + dirs[i][1];
			if (grid[r][c] == ' ') {
				grid[r][c] = mc;
				q.push(make_pair(r, c));
			}
		}
	}
	return true;
}

int main()
{
	while (true) {
		int nr_lines = 0;
		if (!gets(grid[nr_lines]))
			break;
		while (true) {
			nr_lines++;
			if (grid[nr_lines - 1][0] == '_')
				break;
			nr_columns[nr_lines - 1] = strlen(grid[nr_lines - 1]);
			gets(grid[nr_lines]);
		}
		char contour_char = -1;
		for (int i = 0; i < nr_lines - 1; i++)
			for (int j = 0; j < nr_columns[i]; j++)
				if (grid[i][j] != ' ' && grid[i][j] != contour_char) {
					if (is_zone(nr_lines - 1, i, j))
						mark_zone(nr_lines - 1, i, j);
					else
						contour_char = grid[i][j];
				}
		for (int i = 0; i < nr_lines; i++)
			puts(grid[i]);
	}
	return 0;
}

