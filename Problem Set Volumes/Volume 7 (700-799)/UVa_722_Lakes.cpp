
/*
	UVa 722 - Lakes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_722_Lakes.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int r_max = 99, c_max = 99;
char grid[r_max + 1][c_max + 1];

int bfs(int r, int c, int rs, int cs)
{
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] =
		{make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
	queue< pair<int, int> > q;
	int nr = 0;
	if (grid[rs][cs] == '0') {
		nr++;
		grid[rs][cs] = 0;
		q.push(make_pair(rs, cs));
	}
	while (!q.empty()) {
		pair<int, int> i = q.front(); q.pop();
		for (int j = 0; j < nr_dirs; j++) {
			int rj = i.first + dirs[j].first, cj = i.second + dirs[j].second;
			if (rj >= 0 && rj < r && cj >= 0 && cj < c && grid[rj][cj] == '0') {
				nr++;
				grid[rj][cj] = 0;
				q.push(make_pair(rj, cj));
			}
		}
	}
	return nr;
}

int main()
{
	int M;
	scanf("%d", &M);
	while (getchar() != '\n')
		;
	getchar(); // skip g blank line
	while (M--) {
		int rs, cs;
		scanf("%d %d", &rs, &cs);
		rs--; cs--;
		while (getchar() != '\n')
			;
		int r = 0;
		while (gets(grid[r]) && grid[r][0] != '\0') {
			r++;
		}
		int c = strlen(grid[0]);
		printf("%d\n", bfs(r, c, rs, cs));
		if (M)
			putchar('\n');
	}
	return 0;
}

