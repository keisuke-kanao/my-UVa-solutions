
/*
	UVa 639 - Don't Get Rooked

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_639_Dont_Get_Rooked.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

bool is_rook_legal(int n, int r, int c, const vector< vector<char> >& board)
{
	for (int i = r - 1; i >= 0; i--) { // check the up side
		if (board[i][c] == 'R')
			return false;
		else if (board[i][c] == 'X')
			break;
	}
	for (int i = r + 1; i < n; i++) { // check the down side
		if (board[i][c] == 'R')
			return false;
		else if (board[i][c] == 'X')
			break;
	}
	for (int i = c - 1; i >= 0; i--) { // check the left side
		if (board[r][i] == 'R')
			return false;
		else if (board[r][i] == 'X')
			break;
	}
	for (int i = c + 1; i < n; i++) { // check the right side
		if (board[r][i] == 'R')
			return false;
		else if (board[r][i] == 'X')
			break;
	}
	return true;
}

void place_rooks(int n, int nr_squares, int nr_tried /* number of squares tried so far */, const vector<int>& squares,
	vector< vector<char> >& board, int nr_rooks, int& max_nr_rooks)
{
	if (nr_rooks + (nr_squares - nr_tried) <= max_nr_rooks)
		; // no need to further search
	else if (nr_tried == nr_squares) {
		if (nr_rooks > max_nr_rooks)
			max_nr_rooks = nr_rooks;
	}
	else {
		int r = squares[nr_tried] / n, c = squares[nr_tried] % n;
		if (is_rook_legal(n, r, c, board)) { // if legal, place a rook
			board[r][c] = 'R';
			place_rooks(n, nr_squares, nr_tried + 1, squares, board, nr_rooks + 1, max_nr_rooks);
			board[r][c] = '.';
		}
		// proceed without placing a rook
		place_rooks(n, nr_squares, nr_tried + 1, squares, board, nr_rooks, max_nr_rooks);
	}
}

int main()
{
	while (true) {
		int n; // size of a board
		cin >> n;
		if (!n)
			break;
		vector< vector<char> > board(n, vector<char>(n));
		int nr_squares = 0; // number of squares that a rook can be placed
		vector<int> squares(n * n); // vector of squares indices
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> board[i][j];
				if (board[i][j] == '.')
					squares[nr_squares++] = i * n + j;
			}
		int max_nr_rooks = -1; // max. number of rooks that can be placed
		place_rooks(n, nr_squares, 0, squares, board, 0, max_nr_rooks);
		cout << max_nr_rooks << endl;
	}
	return 0;
}

