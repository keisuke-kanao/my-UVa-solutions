
/*
	UVa 10937 - Blackbeard the Pirate

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10937_Blackbeard_the_Pirate.cpp

	This problem is similar to 10944 - Nuts for nuts..
*/

#include <algorithm>
#include <queue>
#include <utility>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int h_max = 50, w_max = 50, nr_treasures_max = 10;
char map[h_max][w_max + 1];
struct place {
	int r_, c_;
	place() {}
	place(int r, int c) : r_(r), c_(c) {}
	place(const place& p) : r_(p.r_), c_(p.c_) {}
} places[nr_treasures_max + 1];

bool visited[h_max][w_max];
int distances[nr_treasures_max + 1][nr_treasures_max + 1];
	// distances[i][j] is the distance between the treasures of i and j
int bitmasks[1 << (nr_treasures_max + 1)][nr_treasures_max + 1];

const int nr_cardinal_dirs = 4;
const pair<int, int> cardinal_dirs[nr_cardinal_dirs] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};
const int nr_diagonal_dirs = 4;
const pair<int, int> diagonal_dirs[nr_diagonal_dirs] = {make_pair(1, 1), make_pair(-1, 1), make_pair(-1, -1), make_pair(1, -1)};

int tsp(int nr_treasures, int places, int p) // travelling salesman problem
{
	if (places == (1 << p))
		return distances[p][0]; // distance from the landing point to the treasure of p
	int& d = bitmasks[places][p];
	if (d >= 0)
		return d;
	d = infinite;
	for (int i = 0; i < nr_treasures; i++)
		if (i != p && (places & (1 << i)))
			d = min(d, distances[p][i] + tsp(nr_treasures, places & ~(1 << p), i));
	return d;
}

int bfs(int h, int w, int s, int nr_treasures)
{
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < nr_treasures; i++)
		distances[s][i] = infinite;
	queue< pair<place, int> > q;
	visited[places[s].r_][places[s].c_] = true;
	distances[s][s] = 0;
	q.push(make_pair(places[s], 0));
	while (!q.empty()) {
		place p = q.front().first;
		int d = q.front().second;
		q.pop();
		for (int i = 0; i < nr_cardinal_dirs; i++) {
			int nr = p.r_ + cardinal_dirs[i].first, nc = p.c_ + cardinal_dirs[i].second;
			if (nr >= 0 && nr < h && nc >= 0 && nc < w && map[nr][nc] != -1 && !visited[nr][nc]) {
				visited[nr][nc] = true;
				if (map[nr][nc] < nr_treasures)
					distances[s][map[nr][nc]] = distances[map[nr][nc]][s] = d + 1;
				q.push(make_pair(place(nr, nc), d + 1));
			}
		}
	}
	for (int i = 0; i < nr_treasures; i++)
		if (distances[s][i] == infinite)
			return -1;
	return 0;
}

int main()
{
	while (true) {
		int h, w;
		scanf("%d %d", &h, &w);
		if (!h)
			break;
		int nr_treasures = 1;
		for (int r = 0; r < h; r++) {
			scanf("%s", map[r]);
			for(int c = 0; c < w; c++)
				switch (map[r][c]) {
				case '@':
					places[0].r_ = r, places[0].c_ = c;
					map[r][c] = 0;
					break;
				case '!':
					places[nr_treasures].r_ = r, places[nr_treasures].c_ = c;
					map[r][c] = nr_treasures++;
					break;
				case '~': case '#':
					map[r][c] = -1;
						break;
				}
		}
		int result = 0;
		for (int r = 0; r < h; r++)
			for(int c = 0; c < w; c++)
				if (map[r][c] == '*') {
					for (int i = 0; i < nr_cardinal_dirs; i++) {
						int nr = r + cardinal_dirs[i].first, nc = c + cardinal_dirs[i].second;
						if (nr >= 0 && nr < h && nc >= 0 && nc < w && map[nr][nc] != '*') {
							if (map[nr][nc] >= 0 && map[nr][nc] < nr_treasures)
								result = -1; // a treasure is not reachable
							map[nr][nc] = -1;
						}
						if (result == -1)
							break;
					}
					for (int i = 0; i < nr_diagonal_dirs; i++) {
						int nr = r + diagonal_dirs[i].first, nc = c + diagonal_dirs[i].second;
						if (nr >= 0 && nr < h && nc >= 0 && nc < w && map[nr][nc] != '*') {
							if (map[nr][nc] >= 0 && map[nr][nc] < nr_treasures)
								result = -1;
							map[nr][nc] = -1;
						}
						if (result == -1)
							break;
					}
					if (result == -1)
						break;
				}
		if (result != -1) {
			// calculate the distances between the treasures/landing point
			for (int i = 0; i < nr_treasures; i++)
				if ((result = bfs(h, w, i, nr_treasures)) == -1)
					break;
			if (result != -1) {
				memset(bitmasks, -1, sizeof(bitmasks));
				result = tsp(nr_treasures, (1 << nr_treasures) - 1, 0);
			}
		}
		printf("%d\n", result);
	}
	return 0;
}

