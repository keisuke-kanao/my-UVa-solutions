
/*
	UVa 11624 - Fire!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11624_Fire.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

const int R_max = 1000, C_max = 1000;
char maze[R_max][C_max + 1];

int bfs(int R, int C, int jr, int jc)
{
	const int nr_dirs = 4;
	int dirs[nr_dirs][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	queue< pair<pair<int, int>, int> > q;
	q.push(make_pair(make_pair(jr, jc), 0));
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
			if (maze[r][c] == 'F')
				q.push(make_pair(make_pair(r, c), -1));
	while (!q.empty()) {
		pair<pair<int, int>, int> s = q.front(); q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			int r = s.first.first + dirs[i][0], c = s.first.second + dirs[i][1];
			if (r < 0 || r >= R || c < 0 || c >= C) {
				if (maze[s.first.first][s.first.second] == 'J')
					return s.second + 1;
			}
			else if (maze[s.first.first][s.first.second] == 'J') {
				if (maze[r][c] == '.') {
					maze[r][c] = 'J';
					q.push(make_pair(make_pair(r, c), s.second + 1));
				}
			}
			else { // maze[s.first][s.second] == 'F'
				if (maze[r][c] == '.' || maze[r][c] == 'J') {
					maze[r][c] = 'F';
					q.push(make_pair(make_pair(r, c), -1));
				}
			}
		}
	}
	return -1;
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		int R, C;
		scanf("%d %d", &R, &C);
		int jr = -1, jc = -1;
		for (int r = 0; r < R; r++) {
			scanf("%s", maze[r]);
			if (jr == -1) {
				for (int c = 0; c < C; c++)
					if (maze[r][c] == 'J') {
						jr = r; jc = c; break;
					}
			}
		}
		int minutes = bfs(R, C, jr, jc);
		if (minutes == -1)
			puts("IMPOSSIBLE");
		else
			printf("%d\n", minutes);
	}
	return 0;
}

