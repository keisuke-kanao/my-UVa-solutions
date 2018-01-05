
/*
	UVa 11101 - Mall Mania

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11101_Mall_Mania.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int x_max = 2000, y_max = 2000;

int bfs(int px_max, int py_max, const pair<int, int>& s, const vector< pair<int, int> >& perimeters)
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	vector< vector<bool> > visited(px_max + 1, vector<bool>(py_max + 1, false));
	queue< pair< pair<int, int>, int> > q;
	visited[s.first][s.second] = true;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair< pair<int, int>, int> p = q.front(); q.pop();
		if (binary_search(perimeters.begin(), perimeters.end(), p.first))
			return p.second;
		for (int i = 0; i < nr_dirs; i++) {
			int x = p.first.first + dirs[i][0], y = p.first.second + dirs[i][1];
			if (x >= 0 && x <= px_max && y >= 0 && y <= py_max && !visited[x][y]) {
				visited[x][y] = true;
				q.push(make_pair(make_pair(x, y), p.second + 1));
			}
		}
	}
	return -1; // to suppress the compiler's warning
}

int main()
{
	while (true) {
		int n, m;
		cin >> n;
		if (!n)
			break;
		int px_min = x_max + 1, py_min = y_max + 1, px_max = -1, py_max = -1;
		vector< pair<int, int> > one_perimeters(n);
		for (int i = 0; i < n; i++) {
			cin >> one_perimeters[i].first >> one_perimeters[i].second;
			px_min = min(px_min, one_perimeters[i].first);
			px_max = max(px_max, one_perimeters[i].first);
			py_min = min(py_min, one_perimeters[i].second);
			py_max = max(py_max, one_perimeters[i].second);
		}
		cin >> m;
		vector< pair<int, int> > other_perimeters(m);
		for (int i = 0; i < m; i++) {
			cin >> other_perimeters[i].first >> other_perimeters[i].second;
			px_min = min(px_min, other_perimeters[i].first);
			px_max = max(px_max, other_perimeters[i].first);
			py_min = min(py_min, other_perimeters[i].second);
			py_max = max(py_max, other_perimeters[i].second);
		}
		for (int i = 0; i < n; i++) {
			one_perimeters[i].first -= px_min; one_perimeters[i].second -= py_min;
		}
		for (int i = 0; i < m; i++) {
			other_perimeters[i].first -= px_min; other_perimeters[i].second -= py_min;
		}
		px_max -= px_min; py_max -= py_min;
		int min_d = px_max + py_max + 1;
		if (n < m) {
			sort(other_perimeters.begin(), other_perimeters.end());
			for (int i = 0; i < n; i++)
				min_d = min(min_d, bfs(px_max, py_max, one_perimeters[i], other_perimeters));
		}
		else {
			sort(one_perimeters.begin(), one_perimeters.end());
			for (int i = 0; i < m; i++)
				min_d = min(min_d, bfs(px_max, py_max, other_perimeters[i], one_perimeters));
		}
		cout << min_d << endl;
	}
	return 0;
}

