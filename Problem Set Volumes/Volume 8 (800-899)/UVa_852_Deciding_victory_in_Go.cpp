
/*
	UVa 852 - Deciding victory in Go

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_852_Deciding_victory_in_Go.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

const int nr_rows = 9, nr_columns = 9;
char board[nr_rows][nr_columns + 1];

int bfs(int r, int c)
{
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};
	int color = 0, nr = 1;
	queue< pair<int, int> > q;
	board[r][c] = 0;
	q.push(make_pair(r, c));
	while (!q.empty()) {
		int pr = q.front().first, pc = q.front().second;
		q.pop();
		for (int i = 0; i < nr_dirs; i++) {
			r = pr + dirs[i].first; c = pc + dirs[i].second;
			if (r >= 0 && r < nr_rows && c >= 0 && c < nr_columns) {
				switch (board[r][c]) {
				case 'X':
					color |= 1; break;
				case 'O':
					color |= 2; break;
				case '.':
					nr++;
					board[r][c] = 0;
					q.push(make_pair(r, c));
					break;
				default:
					break;
				}
			}
		}
	}
	if (color == 1) // surrounded only by blacks
		return nr;
	else if (color == 2) // surrounded only by whites
		return -nr;
	else
		return 0;
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		for (int r = 0; r < nr_rows; r++)
			scanf("%s", board[r]);
		int nr, nr_blacks = 0, nr_whites = 0;
		for (int r = 0; r < nr_rows; r++)
			for (int c = 0; c < nr_columns; c++)
				switch (board[r][c]) {
				case 'X':
					nr_blacks++; break;
				case 'O':
					nr_whites++; break;
				case '.':
					nr = bfs(r, c);
					if (nr > 0)
						nr_blacks += nr;
					else if (nr < 0)
						nr_whites += -nr;
					break;
				default:
					break;
				}
		printf("Black %d White %d\n", nr_blacks, nr_whites);
	}
	return 0;
}

