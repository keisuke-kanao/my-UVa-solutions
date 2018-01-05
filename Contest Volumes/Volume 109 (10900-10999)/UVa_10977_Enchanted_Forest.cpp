
/*
	UVa 10977 - Enchanted Forest

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10977_Enchanted_Forest.cpp
*/

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int R_max = 200, C_max = 200;
bool grid[R_max + 1][C_max + 1];
bool visited[R_max + 1][C_max + 1];

const int nr_dirs = 4;
pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};

int main()
{
	while (true) {
		int R, C;
		cin >> R >> C;
		if (!R && !C)
			break;

		for (int r = 1; r <= R; r++)
			for (int c = 1; c <= C; c++) {
				grid[r][c] = true;
				visited[r][c] = false;
			}
		int m;
		cin >> m;
		while (m--) {
			int r, c;
			cin >> r >> c;
			grid[r][c] = false;
		}
		int n;
		cin >> n;
		while (n--) {
			int r, c, L;
			cin >> r >> c >> L;
			if (!L)
				continue;
			int rs = max(r - L, 1), re = min(r + L, R),
				cs = max(c - L, 1), ce = min(c + L, C), ls = L * L;
			for (int i = rs; i <= re; i++)
				for (int j = cs; j <= ce; j++)
					if ((i - r) * (i - r) + (j - c) * (j - c) <= ls)
						grid[i][j] = false;
		}

#ifdef DEBUG
		for (int r = 1; r <= R; r++) {
			for (int c = 1; c <= C; c++)
				cout << grid[r][c] << ' ';
			cout << endl;
		}
#endif
/*
		if (R == 1 && C == 1) { // already left the forest
			cout << 0 << endl;
			continue;
		}
*/
		// breadth-first search
		queue< pair< pair<int, int>, int> > q;
		bool impossible = true;
		int path = 0;
		if (grid[1][1]) {
			visited[1][1] = true;
			q.push(make_pair(make_pair(1, 1), path));
		}
		while (!q.empty()) {
			pair< pair<int, int>, int> p = q.front(); q.pop();
			path = p.second;
			if (p.first.first == R && p.first.second == C) {
				impossible = false;
				break;
			}
			path++;
			for (int i = 0; i < nr_dirs; i++) {
				int r = p.first.first + dirs[i].first, c = p.first.second + dirs[i].second;
				if (r >= 1 && r <= R && c >= 1 && c <= C && grid[r][c] && !visited[r][c]) {
					visited[r][c] = true;
					q.push(make_pair(make_pair(r, c), path));
				}
			}
		}
		if (impossible)
			cout << "Impossible.\n";
		else
			cout << path << endl;
	}
	return 0;
}

