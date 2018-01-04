
/*
	UVa 11561 - Getting Gold

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11561_Getting_Gold.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int W_max = 50, H_max = 50;
char map[H_max][W_max + 1];
bool drafted[H_max][W_max], visited[H_max][W_max];

const int nr_dirs = 4;
const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void mark_drafted(int H, int W, int r, int c)
{
	for (int i = 0; i < nr_dirs; i++) {
		int dr = r + dirs[i][0], dc = c + dirs[i][1];
		if (dr >= 0 && dr < H && dc >= 0 && dc < W)
			drafted[dr][dc] = true;
	}
}

int bfs(int H, int W, int pr, int pc)
{
	if (drafted[pr][pc])
		return 0;
	int nr = 0;
	queue< pair<int, int> > q;
	visited[pr][pc] = true;
	q.push(make_pair(pr, pc));
	while (!q.empty()) {
		pair<int, int> g = q.front();
		q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			int r = g.first + dirs[i][0], c = g.second + dirs[i][1];
			if (r >= 0 && r < H && c >= 0 && c < W && map[r][c] != '#' && !visited[r][c]) {
				visited[r][c] = true;
				if (map[r][c] == 'G')
					nr++;
				if (!drafted[r][c])
					q.push(make_pair(r, c));
			}
		}
	}
	return nr;
}

int main()
{
	int W, H;
	while (scanf("%d %d", &W, &H) != EOF) {
		for (int r = 0; r < H; r++)
			scanf("%s", map[r]);
		memset(drafted, 0, sizeof(drafted));
		memset(visited, 0, sizeof(visited));
		int pr, pc;
		for (int r = 0; r < H; r++)
			for (int c = 0; c < W; c++) {
				if (map[r][c] == 'P') {
					pr = r; pc = c;
				}
				else if (map[r][c] == 'T')
					mark_drafted(H, W, r, c);
			}
		printf("%d\n", bfs(H, W, pr, pc));
	}
	return 0;
}

