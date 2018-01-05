
/*
	UVa 11049 - Basic wall maze

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11049_Basic_wall_maze.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_rows = 6, nr_columns = 6;
/*
enum {dir_s, dir_n, dir_e, dir_w};
const int nr_dirs = 4;
const char cdirs[nr_dirs] = {'S', 'N', 'E', 'W'};
const int dirs[nr_dirs][2] = {{1, 0}, {-1, 0}, {0, 1}, { 0, -1}};
*/
enum {dir_e, dir_w, dir_n, dir_s};
const int nr_dirs = 4;
const char cdirs[nr_dirs] = {'E', 'W', 'N', 'S'};
const int dirs[nr_dirs][2] = {{0, 1}, { 0, -1}, {-1, 0}, {1, 0}};

bool walls[nr_rows][nr_columns][nr_dirs];
bool visited[nr_rows][nr_columns];
pair<int, int> parents[nr_rows][nr_columns];

void print_path(const pair<int, int>& s)
{
	const pair<int, int>& ps = parents[s.first][s.second];
	if (ps.first != -1) {
		print_path(ps);
		int dir;
		if (ps.first < s.first)
			dir = dir_s;
		else if (ps.first > s.first)
			dir = dir_n;
		else if (ps.second < s.second)
			dir = dir_e;
		else
			dir = dir_w;
		putchar(cdirs[dir]);
	}
}

int main()
{
	while (true) {
		pair<int, int> ss, se;
		scanf("%d %d", &ss.second, &ss.first);
		if (!ss.first && !ss.second)
			break;
		ss.first--; ss.second--;
		scanf("%d %d", &se.second, &se.first);
		se.first--; se.second--;
		memset(walls, 0, sizeof(walls));
		for (int i = 0; i < 3; i++) {
			pair<int, int> ws, we;
			scanf("%d %d %d %d", &ws.second, &ws.first, &we.second, &we.first);
			if (ws.first == we.first) { // horizontal wall
				if (ws.first)
					for (int c = ws.second; c < we.second; c++)
						walls[ws.first - 1][c][dir_n] = true;
				if (ws.first < nr_rows)
					for (int c = ws.second; c < we.second; c++)
						walls[ws.first][c][dir_s] = true;
			}
			else { // vertical wall
				if (ws.second)
					for (int r = ws.first; r < we.first; r++)
						walls[r][ws.second - 1][dir_w] = true;
				if (ws.second < nr_columns)
					for (int r = ws.first; r < we.first; r++)
						walls[r][ws.second][dir_e] = true;
			}
		}

		// breadth first search
		memset(visited, 0, sizeof(visited));
		queue< pair<int, int> > sq;
		visited[ss.first][ss.second] = true;
		parents[ss.first][ss.second] = make_pair(-1, -1);
		sq.push(ss);
		while (!sq.empty()) {
			pair<int, int> s = sq.front(); sq.pop();
			if (s == se)
				break;
			for (int i = 0; i < nr_dirs; i++) {
				int r = s.first + dirs[i][0], c = s.second + dirs[i][1];
				if (r >= 0 && r < nr_rows && c >= 0 && c < nr_columns &&
					!walls[r][c][i] && !visited[r][c]) {
					visited[r][c] = true;
					parents[r][c] = s;
					sq.push(make_pair(r, c));
				}
			}
		}
		print_path(se);
		putchar('\n');
	}
	return 0;
}

