
/*
	UVa 11487 - Gathering Food

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_11487_Gathering_Food.cpp
*/

#include <algorithm>
#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

/*
https://uva.onlinejudge.org/board/viewtopic.php?f=42&t=42308

The total number of paths can be found by basic dynamic programming.
Suppose we have 4 letters {A B C D}.

Total Number of paths = TNP (for the sake of brevity)
Result = TNP(from A to B) * TNP(from B to C) * TNP(from C to D).

So basically, what we need is to find the total number of paths from a point to that of another.
Suppose are going from A to B and let the shortest path be equal to 10.
Lets make a move from A. 
If the shortest path from the new position to B is equal to 9, 
then that point must be a part of the path. You can use dp to memoize repeated states.
*/

#include <algorithm>
#include <queue>
#include <utility>
#include <cstdio>
#include <cctype>
using namespace std;

const int N_max = 10, nr_foods_max = 'Z' - 'A' + 1, modulo = 20437;
const int nr_dirs = 4;
const pair<int, int> dirs[nr_dirs] = {
	make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1)
};
char grid[N_max][N_max + 1];
int N, nr_foods;
pair<int, int>  food_positions[nr_foods_max];
int shortest_paths[nr_foods_max]; // shortest_paths[f] is the length of shortest path from ('A' + f - 1) food to ('A' + f) food
bool visited[N_max][N_max];
int nr_shortest_paths[N_max][N_max][nr_dirs * N_max * N_max];
	// nr_shortest_paths[r][c][l] is the number of shortest paths from grid[r][c] with the path of l length

int bfs(int f) // calculate the the length of shortest path from ('A' + f - 1) to ('A' + f)
{
	const pair<int, int>& s = food_positions[f - 1], e = food_positions[f];
	memset(visited, 0, sizeof(visited));
	queue< pair<pair<int, int>, int> > q;
	visited[s.first][s.second] = true;
	q.push(make_pair(make_pair(s.first, s.second), 0));
	while (!q.empty()) {
		pair<pair<int, int>, int> p = q.front();
		q.pop();
		if (p.first == e)
			return p.second;
		for (int i = 0; i < nr_dirs; i++) {
			int r = p.first.first + dirs[i].first, c = p.first.second + dirs[i].second;
			if (r >= 0 && r < N && c >= 0 && c < N && grid[r][c] != '#' && !visited[r][c]) {
				if (isupper(grid[r][c])) {
					if (grid[r][c] - 'A' <= f) {
						visited[r][c] = true;
						q.push(make_pair(make_pair(r, c), p.second + 1));
					}
				}
				else {
					visited[r][c] = true;
					q.push(make_pair(make_pair(r, c), p.second + 1));
				}
			}
		}
	}
	return -1; // unreachable
}

int dp(int f, int r, int c, int l)
{
	int& nrsp = nr_shortest_paths[r][c][l];
	if (nrsp != -1)
		return nrsp;
	if (!l)
		nrsp = (r == food_positions[f].first && c == food_positions[f].second) ? 1 : 0;
	else {
		nrsp = 0;
		for (int i = 0; i < nr_dirs; i++) {
			int nr = r + dirs[i].first, nc = c + dirs[i].second;
			if (nr >= 0 && nr < N && nc >= 0 && nc < N && grid[nr][nc] != '#') {
				if (isupper(grid[nr][nc])) {
					if (grid[nr][nc] - 'A' <= f)
						nrsp += dp(f, nr, nc, l - 1);
				}
				else
					nrsp += dp(f, nr, nc, l - 1);
			}
		}
	}
	return nrsp;
}

int main()
{
	for (int cn = 1; ; cn++) {
		scanf("%d", &N);
		if (!N)
			break;
		nr_foods = 0;
		for (int r = 0; r < N; r++) {
			scanf("%s", grid[r]);
			for (int c = 0; c < N; c++) {
				if (isupper(grid[r][c])) {
					food_positions[grid[r][c] - 'A'] = make_pair(r, c);
					nr_foods = max(nr_foods, grid[r][c] - 'A' + 1);
				}
			}
		}
		pair<int, int> result = make_pair(-1, 0);
		if (nr_foods) {
			int f;
			for (f = 1; f < nr_foods; f++)
				if ((shortest_paths[f] = bfs(f)) == -1)
					break;
			if (f == nr_foods) {
				result = make_pair(0, 1);
				for (int f = 1; f < nr_foods; f++) {
					result.first += shortest_paths[f];
					memset(nr_shortest_paths, -1, sizeof(nr_shortest_paths));
					result.second *= dp(f, food_positions[f - 1].first, food_positions[f - 1].second, shortest_paths[f]);
					result.second %= modulo;
#ifdef DEBUG
					printf("%c: %d %d\n", 'A' + f, result.first, result.second);
#endif
				}
			}
		}
		printf("Case %d: ", cn);
		if (result.first != -1)
			printf("%d %d\n", result.first, result.second);
		else
			puts("Impossible");
	}
	return 0;
}

