
/*
	UVa 10653 - Bombs! NO they are Mines!!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10653_Bombs_NO_they_are_Mines.cpp
*/

#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int nr_rows_max = 1000, nr_columns_max = 1000;
bool grid[nr_rows_max][nr_columns_max];
bool visited[nr_rows_max][nr_columns_max];
const int nr_dirs = 4;
const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int bfs(int nr_rows, int nr_columns, const pair<int, int>& s, const pair<int, int>& d)
{
	queue< pair< pair<int, int>, int>  > q;
	for (int i = 0; i < nr_rows; i++)
		for (int j = 0; j < nr_columns; j++)
			visited[i][j] = false;
	visited[s.first][s.second] = true;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair< pair<int, int>, int> i = q.front(); q.pop();
		if (i.first == d)
			return i.second;
		for (int j = 0; j < nr_dirs; j++) {
			int r = i.first.first + dirs[j][0], c = i.first.second + dirs[j][1];
			if (r >= 0 && r < nr_rows && c >= 0 && c < nr_columns && !grid[r][c] && !visited[r][c]) {
				visited[r][c] = true;
				q.push(make_pair(make_pair(r, c), i.second + 1));
			}
		}
	}
	return -1;
}

int main()
{
	while (true) {
		int nr_rows, nr_columns;
		cin >> nr_rows >> nr_columns;
		if (!nr_rows && !nr_columns)
			break;
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++)
				grid[i][j] = false;
		int nr_locations;
		cin >> nr_locations;
		for (int i = 0; i < nr_locations; i++) {
			int r, nr_bombs;
			cin >> r >> nr_bombs;
			for (int j = 0; j < nr_bombs; j++) {
				int c;
				cin >> c;
				grid[r][c] = true;
			}
		}
		pair<int, int> s, d;
		cin >> s.first >> s.second >> d.first >> d.second;
		cout << bfs(nr_rows, nr_columns, s, d) << endl;
	}
	return 0;
}

