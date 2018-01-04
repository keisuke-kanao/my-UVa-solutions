
/*
	UVa 260 - Il Gioco dell'X

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_260_Il_Gioco_dellX.cpp
*/

#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
using namespace std;

const int n_max = 200;
char board[n_max][n_max];
bool rows[n_max];

bool bfs(int n, int i, int j)
{
	const pair<int, int> dirs[] = {
		make_pair(-1, -1), make_pair(-1, 0), make_pair(0, -1), make_pair(0, 1), make_pair(1, 0), make_pair(1, 1)
	};

	queue< pair<int, int> > q;
	memset(rows, 0, sizeof(rows));
	rows[i] = true;
	board[i][j] = 0;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (size_t k = 0, l = sizeof(dirs) / sizeof(pair<int, int>); k < l; k++) {
			i = p.first + dirs[k].first;
			j = p.second + dirs[k].second;
			if (i >= 0 && i < n && j >= 0 && j < n && board[i][j] == 'b') {
				rows[i] = true;
				board[i][j] = 0;
				q.push(make_pair(i, j));
			}
		}
	}
	bool black_win = true;
	for (int i = 0; i < n; i++)
		if (!rows[i]) {
			black_win = false;
			break;
		}
	return black_win;
}

int main()
{
	for (int g = 1; ; g++) {
		int n;
		cin >> n;
		if (!n)
			break;
		int i, j;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				cin >> board[i][j];
		bool black_win = false;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				if (board[i][j] == 'b' && (black_win = bfs(n, i, j)))
					break;
			if (black_win)
				break;
		}
		cout << g << ' ' << ((black_win) ? "B\n" : "W\n");
	}
	return 0;
}

