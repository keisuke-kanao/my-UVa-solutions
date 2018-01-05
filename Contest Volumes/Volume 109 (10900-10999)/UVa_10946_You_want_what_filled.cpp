
/*
	UVa 10946 - You want what filled?

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10946_You_want_what_filled.cpp
*/

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int nr_rows_max = 50, nr_columns_max = 50;
char matrix[nr_rows_max][nr_columns_max];
pair<char, int> holes[nr_rows_max * nr_columns_max];

int bfs(int i, int j, int n, int m)
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
	queue< pair<int, int> > q;
	char c = matrix[i][j];
	matrix[i][j] = '.';
	int count = 1;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int k = 0; k < nr_dirs; k++) {
			i = p.first + dirs[k][0]; j = p.second + dirs[k][1];
			if (i < 0 || i >= n || j < 0 || j >= m || matrix[i][j] != c)
				;
			else {
				matrix[i][j] = '.';
				count++;
				q.push(make_pair(i, j));
			}
		}
	}
	return count;
}

bool compare_hole(const pair<char, int>& i, const pair<char, int>& j)
{
	if (i.second > j.second)
		return true;
	else if (i.second < j.second)
		return false;
	else
		return i.first < j.first;
}

int main()
{
	for (int pn = 1; ; pn++) {
		int nr_rows, nr_columns;
		cin >> nr_rows >> nr_columns;
		if (!nr_rows && !nr_columns)
			break;
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++)
				cin >> matrix[i][j];
		int nr_holes = 0;
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++) {
				char c = matrix[i][j];
				if (c != '.')
					holes[nr_holes++] = make_pair(c, bfs(i, j, nr_rows, nr_columns));
			}
		sort(holes, holes + nr_holes, compare_hole);
		cout << "Problem " << pn << ":\n";
		for (int i = 0; i < nr_holes; i++) {
			cout << holes[i].first << ' ' << holes[i].second << endl;
		}
	}
	return 0;
}

