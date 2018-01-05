
/*
	UVa 11101 - Mall Mania

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11101_Mall_Mania.cpp

	An accepted solution.
*/

#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int x_max = 2000, y_max = 2000;
bool visited[x_max + 1][y_max + 1], perimeters[x_max + 1][y_max + 1];
const int nr_dirs = 4;
const int dirs[nr_dirs][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		memset(visited, 0, sizeof(visited));
		memset(perimeters, 0, sizeof(perimeters));
		queue< pair< pair<int, int>, int> > q;
		while (n--) {
			int x, y;
			scanf("%d %d", &x, &y);
			visited[x][y] = true;
			q.push(make_pair(make_pair(x, y), 0));
		}
		scanf("%d", &n);
		while (n--) {
			int x, y;
			scanf("%d %d", &x, &y);
			perimeters[x][y] = true;
		}
		int min_d = 0;
		while (!q.empty()) {
			pair< pair<int, int>, int> p = q.front(); q.pop();
			if (perimeters[p.first.first][p.first.second]) {
				min_d = p.second; break;
			}
			for (int i = 0; i < nr_dirs; i++) {
				int x = p.first.first + dirs[i][0], y = p.first.second + dirs[i][1];
				if (x >= 0 && x <= x_max && y >= 0 && y <= y_max && !visited[x][y]) {
					visited[x][y] = true;
					q.push(make_pair(make_pair(x, y), p.second + 1));
				}
			}
		}
		printf("%d\n", min_d);
	}
	return 0;
}

