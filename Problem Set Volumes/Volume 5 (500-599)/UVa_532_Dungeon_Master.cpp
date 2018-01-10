
/*
	UVa 532 - Dungeon Master

	To build using Visual Studio 20&08:
		cl -EHsc -O2 UVa_532_Dungeon_Master.cpp

	from ACM University of Ulm Local Contest 1997 Problem D
		(http://www.informatik.uni-ulm.de/acm/Locals/1997/)
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int count_path(int s, int e, int nr_paths, const vector<int>& parents)
{
	if (e == -1)
		return nr_paths;
	else
		return count_path(s, parents[e], nr_paths + 1, parents);
}

int bfs(int n, int s, int e, const vector< vector<int> >& adjacency_list)
{
	vector<bool> visited(n, false);
	vector<int> parents(n, -1);
	queue<int> q;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		if (i == e)
			break;
		for (vector<int>::const_iterator j = adjacency_list[i].begin(), k = adjacency_list[i].end(); j != k; ++j)
			if (!visited[*j]) {
				visited[*j] = true;
				parents[*j] = i;
				q.push(*j);
			}
	}
	return count_path(s, e, 0, parents) - 1;
}

int main()
{
	while (true) {
		int nr_levels, nr_rows, nr_columns;
		cin >> nr_levels >> nr_rows >> nr_columns;
		if (!nr_levels && !nr_rows && !nr_columns)
			break;
		vector< vector< vector<char> > > dungeon(nr_levels, vector< vector<char> >(nr_rows, vector<char>(nr_columns, 0)));
		int s, e;
		for (int i = 0; i < nr_levels; i++)
			for (int j = 0; j < nr_rows; j++)
				for (int k = 0; k < nr_columns; k++) {
					char c;
					cin >> c;
					if (c == 'S') {
						c = '.';
						s = i * (nr_rows * nr_columns) + j * nr_columns + k;
					}
					else if (c == 'E') {
						c = '.';
						e = i * (nr_rows * nr_columns) + j * nr_columns + k;
					}
					dungeon[i][j][k] = c;
				}
		int nr_lists = nr_levels * nr_rows * nr_columns;
		vector< vector<int> > adjacency_list(nr_lists, vector<int>());
		for (int i = 0; i < nr_levels; i++)
			for (int j = 0; j < nr_rows; j++)
				for (int k = 0; k < nr_columns; k++)
					if (dungeon[i][j][k] == '.') {
						int l = i * (nr_rows * nr_columns) + j * nr_columns + k, m;
						if (i && dungeon[i - 1][j][k] == '.') { // up/down
							m = l - (nr_rows * nr_columns);
							adjacency_list[l].push_back(m);
							adjacency_list[m].push_back(l);
						}
						if (j && dungeon[i][j - 1][k] == '.') { // north/south
							m = l - nr_columns;
							adjacency_list[l].push_back(m);
							adjacency_list[m].push_back(l);
						}
						if (k && dungeon[i][j][k - 1] == '.') { // west/east
							m = l - 1;
							adjacency_list[l].push_back(m);
							adjacency_list[m].push_back(l);
						}
					}
		int nr_paths = bfs(nr_lists, s, e, adjacency_list);
		if (nr_paths)
			cout << "Escaped in " << nr_paths << " minute(s).\n";
		else
			cout << "Trapped!\n";
	}
	return 0;
}

