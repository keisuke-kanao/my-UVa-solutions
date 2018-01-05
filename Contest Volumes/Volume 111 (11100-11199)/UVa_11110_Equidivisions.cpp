
/*
	UVa 11110 - Equidivisions

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11110_Equidivisions.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int bfs(int n, int i, int j, vector< vector<int> >& cells)
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	queue< pair<int, int> > q;
	int k = cells[i][j], nr = 0;
	cells[i][j] = 0;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front(); q.pop();
		nr++;
		for (int i = 0; i < nr_dirs; i++) {
			int r = p.first + dirs[i][0], c = p.second + dirs[i][1];
			if (r >= 1 && r <= n && c >= 1 && c <= n && cells[r][c] == k) {
				cells[r][c] = 0;
				q.push(make_pair(r, c));
			}
		}
	}
	return nr;
}

bool is_equidivision(int n, vector< vector<int> >& cells)
{
	vector<bool> regions(n + 1, false); // regions[i] is true if i-th region has n contiguous cells
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int k = cells[i][j];
			if (k) {
				if (regions[k] || bfs(n, i, j, cells) != n)
					return false;
				regions[k] = true;
			}
		}
	return true;
}

int main()
{
	while (true) {
		string line;
		istringstream iss;
		getline(cin, line);
		iss.str(line);
		int n;
		iss >> n;
		iss.clear();
		if (!n)
			break;
		vector< vector<int> > cells(n + 1, vector<int>(n + 1, n));
		for (int k = 1; k <= n - 1; k++) {
			getline(cin, line);
			iss.str(line);
			int i, j;
			while (iss >> i >> j)
				cells[i][j] = k;
			iss.clear();
		}
		cout << ((is_equidivision(n, cells)) ? "good\n" : "wrong\n");
	}
	return 0;
}

