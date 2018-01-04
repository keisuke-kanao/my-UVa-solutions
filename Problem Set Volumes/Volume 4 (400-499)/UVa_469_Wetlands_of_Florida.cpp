
/*
	UVa 469 - Wetlands of Florida

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_469_Wetlands_of_Florida.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <utility>
using namespace std;

const int nr_rows_max = 99, nr_columns_max = 99;
char grid[nr_rows_max][nr_columns_max];
bool visited[nr_rows_max][nr_columns_max];

int bfs(int nr_rows, int nr_columns, int r, int c)
{
	const pair<int, int> dirs[] = {
		make_pair(1, 0), make_pair(1, 1), make_pair(0, 1), make_pair(-1, 1),
		make_pair(-1, 0), make_pair(-1, -1), make_pair(0, -1), make_pair(1, -1)
	};

	if (r < 0 || r >= nr_rows || c < 0 || c >= nr_columns || grid[r][c] != 'W')
		return 0;
	for (int i = 0; i < nr_rows; i++)
		for (int j = 0; j < nr_columns; j++)
			visited[i][j] = false;
	int nr_w = 1;
	queue< pair<int, int> > q;
	visited[r][c] = true;
	q.push(make_pair(r, c));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (size_t i = 0, j = sizeof(dirs) / sizeof(pair<int, int>); i < j; i++) {
			r = p.first + dirs[i].first;
			c = p.second + dirs[i].second;
			if (r >= 0 && r < nr_rows && c >= 0 && c < nr_columns && grid[r][c] == 'W' && !visited[r][c]) {
				visited[r][c] = true;
				nr_w++;
				q.push(make_pair(r, c));
			}
		}
	}
	return nr_w;
}

int main()
{
	string s;
	istringstream iss;
	getline(cin, s);
	iss.str(s);
	int t;
	iss >> t;
	iss.clear();
	getline(cin, s); // skip a blank line
	while (t--) {
		int nr_rows = 0, nr_columns = 0;
		while (true) {
			getline(cin, s);
			if (s[0] != 'L' && s[0] != 'W')
				break;
			if (!nr_columns)
				nr_columns = s.length();
			for (int i = 0; i < nr_columns; i++)
				grid[nr_rows][i] = s[i];
			nr_rows++;
		}
		do {
			iss.str(s);
			int r, c;
			iss >> r >> c;
			cout << bfs(nr_rows, nr_columns, r - 1, c - 1) << endl;
			iss.clear();
		} while (getline(cin, s) && !s.empty());
		if (t)
			cout << endl;
	}
	return 0;
}

