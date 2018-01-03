
/*
	UVa 601 - The PATH

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_601_The_PATH.cpp

	from ACM Pacific Northwest Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_PacNW/1997/index.html)
*/

#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 80;
char board[n_max][n_max + 1];
bool visited[n_max][n_max];

bool bfs(int n, int i, int j, char bw)
{
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	queue< pair<int, int> > q;
	memset(visited, 0, sizeof(visited));
	visited[i][j] = true;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		if (bw == 'W' && p.second == n - 1 || bw == 'B' && p.first == n - 1)
			return true;
		for (int k = 0; k < nr_dirs; k++) {
			i = p.first + dirs[k][0]; j = p.second + dirs[k][1];
			if (i < 0 || i >= n || j < 0 || j >= n || board[i][j] != bw || visited[i][j])
				;
			else {
				visited[i][j] = true;
				q.push(make_pair(i, j));
			}
		}
	}
	return false;
}

bool is_white_winner(int n)
{
	for (int i = 0; i < n; i++)
		if (board[i][0] == 'W' && bfs(n, i, 0, 'W'))
			return true;
	return false;
}

bool is_black_winner(int n)
{
	for (int i = 0; i < n; i++)
		if (board[0][i] == 'B' && bfs(n, 0, i, 'B'))
			return true;
	return false;
}

bool is_white_winner_with_one_move(int n, int nr_unfilled)
{
	for (int i = 0; nr_unfilled && i < n; i++)
		for (int j = 0; nr_unfilled && j < n; j++)
			if (board[i][j] == 'U') {
				nr_unfilled--;
				board[i][j] = 'W';
				if (is_white_winner(n))
					return true;
				board[i][j] = 'U';
			}
	return false;
}

bool is_black_winner_with_one_move(int n, int nr_unfilled)
{
	for (int i = 0; nr_unfilled && i < n; i++)
		for (int j = 0; nr_unfilled && j < n; j++)
			if (board[i][j] == 'U') {
				nr_unfilled--;
				board[i][j] = 'B';
				if (is_black_winner(n))
					return true;
				board[i][j] = 'U';
			}
	return false;
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int nr_unfilled = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", board[i]);
			for (int j = 0; j < n; j++)
				if (board[i][j] == 'U')
					nr_unfilled++;
		}
		if (is_white_winner(n))
			puts("White has a winning path.");
		else if (is_black_winner(n))
			puts("Black has a winning path.");
		else if (is_white_winner_with_one_move(n, nr_unfilled))
			puts("White can win in one move.");
		else if (is_black_winner_with_one_move(n, nr_unfilled))
			puts("Black can win in one move.");
		else
			puts("There is no winning path.");
	}
	return 0;
}

