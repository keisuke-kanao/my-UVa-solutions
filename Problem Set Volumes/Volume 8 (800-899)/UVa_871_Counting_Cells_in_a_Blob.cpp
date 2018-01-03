
/*
	UVa 871 - Counting Cells in a Blob

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_871_Counting_Cells_in_a_Blob.cpp
*/

#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 25;
char grid[n_max + 1][n_max + 1];

int bfs(int r, int c, int nr_rows, int nr_columns)
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	queue< pair<int, int> > q;
	grid[r][c] = '0';
	q.push(make_pair(r, c));
	int nr = 0;
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		nr++;
		for (int k = 0; k < nr_dirs; k++) {
			r = p.first + dirs[k][0]; c = p.second + dirs[k][1];
			if (r < 0 || r >= nr_rows || c < 0 || c >= nr_columns || grid[r][c] == '0')
				;
			else {
				grid[r][c] = '0';
				q.push(make_pair(r, c));
			}
		}
	}
	return nr;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	getchar();
	getchar(); // skip a blank line
	while (nr_cases--) {
		int nr_rows = 0;
		while (gets(grid[nr_rows]) && grid[nr_rows][0])
			nr_rows++;
		int nr_columns = strlen(grid[0]);
		int max_nr_blobs = 0;
		for (int r = 0; r < nr_rows; r++)
			for (int c = 0; c < nr_columns; c++)
				if (grid[r][c] == '1') {
					int nr_blobs = bfs(r, c, nr_rows, nr_columns);
					if (nr_blobs > max_nr_blobs)
						max_nr_blobs = nr_blobs;
				}
		printf("%d\n", max_nr_blobs);
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

