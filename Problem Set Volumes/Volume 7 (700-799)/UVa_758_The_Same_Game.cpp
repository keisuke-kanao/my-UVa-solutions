
/*
	UVa 758 - The Same Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_758_The_Same_Game.cpp

	from ACM East Central Regionals 1999, Problem H
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1999/index.html)

	This problem is similar to UVa 339 - SameGame Simulation.
*/

#include <queue>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_rows = 10, nr_columns = 15;
char board[nr_rows][nr_columns + 1];
bool visited[nr_rows][nr_columns];

struct cluster {
	int sr_, sc_; // start row and column
	int nr_balls_; // number of balls

	bool operator<(const cluster& c) const {
		if (nr_balls_ != c.nr_balls_)
			return nr_balls_ > c.nr_balls_;
		else if (sc_ != c.sc_)
			return sc_ < c.sc_;
		else
			return sr_ < c.sr_;
	}
} clusters[nr_rows * nr_columns];


#ifdef DEBUG
void print_board()
{
	putchar('\n');
	for (int i = 0; i < nr_rows; i++)
		for (int j = 0; j < nr_columns; j++)
			printf("%c%c", ((board[i][j]) ? board[i][j] : ' '), ((j < nr_columns - 1) ? ' ' : '\n'));
}
#endif

int bfs(int sr, int sc, bool remove)
{
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] = {make_pair(-1, 0), make_pair(1, 0), make_pair(0, 1), make_pair(0, -1)};
	char b = board[sr][sc];
	int nr_removed = 0;
	queue< pair<int, int> > q;
	if (remove)
		board[sr][sc] = 0;
	else
		visited[sr][sc] = true;
	q.push(make_pair(sr, sc));
	while (!q.empty()) {
		pair<int, int> i = q.front();
		q.pop();
		for (int j = 0; j < nr_dirs; j++) {
			int r = i.first + dirs[j].first, c = i.second + dirs[j].second;
			if (r >= 0 && r < nr_rows && c >= 0 && c < nr_columns && board[r][c] == b &&
				(remove && board[r][c] || !remove && !visited[r][c])) {
				nr_removed++;
				if (remove)
					board[r][c] = 0;
				else
					visited[r][c] = true;
				q.push(make_pair(r, c));
			}
		}
	}
	if (nr_removed)
		return nr_removed + 1;
	else
		return 0;
}

void remove_balls()
{
	for (int j = 0; j < nr_columns; j++) { // remove cells for each column
		for (int i = 0, k = 1; k < nr_rows; ) {
			if (board[i][j]) {
				if (++i == k)
					k++;
			}
			else {
				for ( ; k < nr_rows; k++)
					if (board[k][j])
						break;
				if (k < nr_rows) {
					board[i][j] = board[k][j];
					board[k][j] = 0;
					i++; k++;
				}
			}
		}
	}
	for (int j = 0, k = 1; k < nr_columns; ) { // remove columns
		if (board[0][j]) {
			if (++j == k)
				k++;
		}
		else {
			for ( ; k < nr_columns; k++)
				if (board[0][k])
					break;
			if (k < nr_columns) {
				for (int i = 0; i < nr_rows; i++) {
					board[i][j] = board[i][k];
					board[i][k] = 0;
				}
				j++; k++;
			}
		}
	}
#ifdef DEBUG
	print_board();
#endif
}

int main()
{
	int ng;
	scanf("%d", &ng);
	for (int g = 1; g <= ng; g++) {
		for (int i = nr_rows - 1; i >= 0; i--)
			scanf("%s", &board[i]);
		printf("Game %d:\n\n", g);
		int score = 0, nr_balls = nr_rows * nr_columns;
		for (int m = 1; ; m++) {
			int nr_clusters = 0;
			memset(visited, 0, sizeof(visited));
			for (int j = 0; j < nr_columns; j++)
				for (int i = 0; i < nr_rows; i++)
					if (board[i][j] && !visited[i][j] &&
						(clusters[nr_clusters].nr_balls_ = bfs(i, j, false)) != 0) {
						clusters[nr_clusters].sr_ = i; clusters[nr_clusters].sc_ = j;
						nr_clusters++;
					}
			if (!nr_clusters)
				break;
			sort(clusters, clusters + nr_clusters);
			int sr = clusters[0].sr_, sc = clusters[0].sc_;
			char b = board[sr][sc];
			int nr = bfs(sr, sc, true), s = (nr - 2) * (nr - 2);
			printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n", m, sr + 1, sc + 1, nr, b, s);
			remove_balls();
			nr_balls -= nr; score += s;
		}
		if (!nr_balls)
			score += 1000;
		printf("Final score: %d, with %d balls remaining.\n", score, nr_balls);
		if (g < ng)
			putchar('\n');
	}
	return 0;
}

