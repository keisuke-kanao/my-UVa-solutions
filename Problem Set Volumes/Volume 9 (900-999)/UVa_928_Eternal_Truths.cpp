
/*
	UVa 928 - Eternal Truths

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_928_Eternal_Truths.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

const int R_max = 300, C_max = 300, nr_steps = 3;
char maze[R_max][C_max + 1];
bool visited[R_max][C_max][nr_steps + 1];

int bfs(int R, int C, const pair<int, int>& s, const pair<int, int>& e)
{
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
			for (int s = 1; s <= nr_steps; s++)
				visited[r][c][s] = false;
	queue< pair<pair<int, int>, int> > q;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair<pair<int, int>, int> p = q.front(); q.pop();
		if (p.first == e)
			return p.second;
		int s = (p.second + 1) % nr_steps;
		if (!s)
			s = nr_steps;
		for (int i = 0; i < nr_dirs; i++)
			for (int j = 1; j <= s; j++) {
				int r = p.first.first + j * dirs[i].first, c = p.first.second + j * dirs[i].second;
				if (r < 0 || r >= R || c < 0 || c >= C || maze[r][c] == '#')
					break;
				if (j == s && !visited[r][c][s]) {
#ifdef DEBUG
					printf("%d %d %d %d\n", r, c, s, p.second + 1);
#endif
					visited[r][c][s] = true;
					q.push(make_pair(make_pair(r, c), p.second + 1));
				}
			}
	}
	return -1;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int R, C;
		scanf("%d %d", &R, &C);
		getchar();
		pair<int, int> s, e;
		s.first = e.first = -1;
		for (int r = 0; r < R; r++) {
			gets(maze[r]);
			for (int c = 0; c < C; c++)
				if (s.first == -1 && maze[r][c] == 'S')
					s = make_pair(r, c);
				else if (e.first == -1 && maze[r][c] == 'E')
					e = make_pair(r, c);
		}
		int nr_moves = bfs(R, C, s, e);
		if (nr_moves != -1)
			printf("%d\n", nr_moves);
		else
			puts("NO");
	}
	return 0;
}

/*

3
5 4
S...
.#.#
.#..
.##.
...E
6 6
.S...E
.#.##.
.#....
.#.##.
.####.
......
6 6
.S.#E.
.#.##.
.#....
.#.##.
.####.
......


NO
3
7

*/

