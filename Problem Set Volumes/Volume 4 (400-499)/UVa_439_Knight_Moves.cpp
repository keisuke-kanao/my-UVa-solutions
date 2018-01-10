
/*
	UVa 439 - Knight Moves

	To build using Visual Studio 20&08:
		cl -EHsc -O2 UVa_439_Knight_Moves.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int nr_rows = 8, nr_columns = 8, nr_squares = 64;

int count_path(int start, int end, int nr_paths, const vector<int>& parents)
{
	if (end == -1)
		return nr_paths;
	else
		return count_path(start, parents[end], nr_paths + 1, parents);
}

bool push_index(int i, int row, int column, vector<bool>& visited, vector<int>& parents, queue<int>& q)
{
	if (row < 0 || row >= nr_rows || column < 0 || column >= nr_columns)
		return false;
	int j = row * nr_columns + column;
	if (!visited[j]) {
		visited[j] = true;
		parents[j] = i;
		q.push(j);
		return true;
	}
	else
		return false;
}

int bfs(int start, int end)
{
	if (start == end)
		return 0;
	vector<bool> visited(nr_squares, false);
	vector<int> parents(nr_squares, -1);
	queue<int> q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		if (i == end)
			break;
		int r = i / nr_columns, c = i % nr_columns;
		push_index(i, r - 2, c - 1, visited, parents, q);
		push_index(i, r - 2, c + 1, visited, parents, q);
		push_index(i, r - 1, c - 2, visited, parents, q);
		push_index(i, r - 1, c + 2, visited, parents, q);
		push_index(i, r + 1, c - 2, visited, parents, q);
		push_index(i, r + 1, c + 2, visited, parents, q);
		push_index(i, r + 2, c - 1, visited, parents, q);
		push_index(i, r + 2, c + 1, visited, parents, q);
	}
	return count_path(start, end, 0, parents) - 1;
}

int main()
{
	char sc, sr, tc, tr;
	while (cin >> sc >> sr >> tc >> tr) {
		int start = nr_columns * (sr - '1') + (sc - 'a'), end = nr_columns * (tr - '1') + (tc - 'a');
		int nr_moves = bfs(start, end);
		cout << "To get from " << sc << sr << " to " << tc << tr << " takes " << nr_moves << " knight moves.\n";
	}
	return 0;
}

