
/*
	UVa 11244 - Counting Stars

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11244_Counting_Stars.cpp
*/

#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int nr_rows_max = 100, nr_columns_max = 100;
char matrix[nr_rows_max][nr_columns_max];

int bfs(int i, int j, int r, int c)
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	queue< pair<int, int> > q;
	matrix[i][j] = '.';
	int count = 1;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int k = 0; k < nr_dirs; k++) {
			i = p.first + dirs[k][0]; j = p.second + dirs[k][1];
			if (i < 0 || i >= r || j < 0 || j >= c || matrix[i][j] == '.')
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
	while (true) {
		int nr_rows, nr_columns;
		cin >> nr_rows >> nr_columns;
		if (!nr_rows && !nr_columns)
			break;
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++)
				cin >> matrix[i][j];
		int nr_stars = 0;
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++)
				if (matrix[i][j] == '*' && bfs(i, j, nr_rows, nr_columns) == 1)
					nr_stars++;
		cout << nr_stars << endl;
	}
	return 0;
}

