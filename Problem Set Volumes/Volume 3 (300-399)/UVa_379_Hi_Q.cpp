
/*
	UVa 379 - Hi-Q

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_379_Hi_Q.cpp

	from ACM Mid Atlantic Regionals 1996 Problem 3
*/

#include <utility>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_rcs = 7; // number of rows/columns in the board
const int peg_max = 33;

const int holes[nr_rcs][nr_rcs] = { // table to get the hole number from its position
	{-1, -1, 1, 2, 3, -1, -1},
	{-1, -1, 4, 5, 6, -1, -1},
	{7, 8, 9,  10, 11, 12, 13},
	{14, 15, 16, 17, 18, 19, 20},
	{21, 22, 23, 24, 25, 26, 27},
	{-1, -1, 28, 29, 30, -1, -1},
	{-1, -1, 31, 32, 33, -1, -1}
};

const pair<int, int> positions[] = { // table to get the position from its hole number
	make_pair(-1, -1),
	make_pair(0, 2), make_pair(0, 3), make_pair(0, 4),
	make_pair(1, 2), make_pair(1, 3), make_pair(1, 4),
	make_pair(2, 0), make_pair(2, 1), make_pair(2, 2), make_pair(2, 3), make_pair(2, 4), make_pair(2, 5), make_pair(2, 6),
	make_pair(3, 0), make_pair(3, 1), make_pair(3, 2), make_pair(3, 3), make_pair(3, 4), make_pair(3, 5), make_pair(3, 6),
	make_pair(4, 0), make_pair(4, 1), make_pair(4, 2), make_pair(4, 3), make_pair(4, 4), make_pair(4, 5), make_pair(4, 6),
	make_pair(5, 2), make_pair(5, 3), make_pair(5, 4),
	make_pair(6, 2), make_pair(6, 3), make_pair(6, 4)
};

int board[nr_rcs][nr_rcs]; // board[i][j] is 1 for a peg, 0 for a hole, -1 for neither of the two

pair<int, int> move_peg(const pair<int, int>& p)
{
	int r = p.first, c = p.second, tp = 0, rp = 0;
	if (r > 1 && board[r - 1][c] == 1 && !board[r - 2][c]) { // up
		tp = holes[r - 2][c]; rp = holes[r - 1][c];
	}
	if (r < nr_rcs - 2 && board[r + 1][c] == 1 && !board[r + 2][c]) { // down
		if (holes[r + 2][c] > tp) {
			tp = holes[r + 2][c]; rp = holes[r + 1][c];
		}
	}
	if (c > 1 && board[r][c - 1] == 1 && !board[r][c - 2]) { // left
		if (holes[r][c - 2] > tp) {
			tp = holes[r][c - 2]; rp = holes[r][c - 1];
		}
	}
	if (c < nr_rcs - 2 && board[r][c + 1] == 1 && !board[r][c + 2]) { // right
		if (holes[r][c + 2] > tp) {
			tp = holes[r][c + 2]; rp = holes[r][c + 1];
		}
	}
	return make_pair(tp, rp);
}

int main()
{
	int n;
	scanf("%d", &n);
	puts("HI Q OUTPUT");
	while (n--) {
		memset(board, -1, sizeof(board));
		for (int p = 1; p <= peg_max; p++)
			board[positions[p].first][positions[p].second] = 0;
		while (true) {
			int p;
			scanf("%d", &p);
			if (!p)
				break;
			board[positions[p].first][positions[p].second] = 1;
		}
		while (true) {
			int max_sp = 0, max_tp = 0, max_rp = 0, sp;
			for (int p = 1; p <= peg_max; p++) {
				pair<int, int> pp = positions[p];
				if (board[pp.first][pp.second]) {
					sp = holes[pp.first][pp.second];
					pair<int, int> tprp = move_peg(pp);
					if (tprp.first) {
						if (tprp.first > max_tp || tprp.first == max_tp && sp > max_sp) {
							max_sp = sp; max_tp = tprp.first; max_rp = tprp.second;
						}
					}
				}
			}
			if (max_tp) {
#ifdef DEBUG
				printf("%d jumps over %d to %d\n", max_sp, max_rp, max_tp);
#endif
				board[positions[max_sp].first][positions[max_sp].second] =
					board[positions[max_rp].first][positions[max_rp].second] = 0;
				board[positions[max_tp].first][positions[max_tp].second] = 1;
			}
			else
				break;
		}
		int s = 0;
		for (int p = 1; p <= peg_max; p++) {
			pair<int, int> pp = positions[p];
			if (board[pp.first][pp.second])
				s += holes[pp.first][pp.second];
		}
		printf("%d\n", s);
	}
	puts("END OF OUTPUT");
	return 0;
}

