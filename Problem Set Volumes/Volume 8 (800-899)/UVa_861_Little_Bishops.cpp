
/*
	8.6.1 Little Bishops
	PC/UVa IDs: 110801/861, Popularity: C, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_861_Little_Bishops.cpp
*/

/*
Each square in the chessboard is represented by its vertical row and horizontal column positions (row, column).

For a n * n chessboard, there are (2 * n - 1) diagonals.

Let the diagonals index from left top to right bottom and the squres in each diagonal index from left to 
right, then, the diagonals and thier squares are as follows:
	diagonal	square
	----------------------------------------------------------------------------
	0			(0, 0)
	1			(1, 0), (0, 1)
	2			(2, 0), (1, 1), (0, 2)
	...
	(n - 1)		(n - 1, 0), (n - 2, 1), (n - 2, 2), ..., (1, n - 2), (0, n - 1)
	n			(n - 1, 1), (n - 2, 2), (n - 3, 3), ..., (2, n - 2), (1, n - 1)
	...
	(2 * n - 3)	(n - 1, n - 2), (n - 2, n - 1)
	(2 * n - 2)	(n - 1, n - 1)
*/

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

typedef pair<int, int> square; // first field is row, second field is column

bool is_attacking_position(const square& s, int nr_squares, const vector<square>& squares)
// see if a given square is an attacking position for the already arranged squares
{
	for (int i = 0; i < nr_squares; i++) {
		if (squares[i] == square(-1, -1))
			continue;
		if (abs(s.first - squares[i].first) == abs(s.second - squares[i].second))
			return true;
	}
	return false;
}

void arrange_bishops(int n, int bishops, int diagonal, vector<square>& squares, int& arrangements)
{
	if (!bishops) {
		arrangements++;
		return;
	}
	int nr_squares; // number of squares in the diagonal
	int row, column; // left most squre position in the diagonal
	if (diagonal < n) {
		nr_squares = diagonal + 1;
		row = diagonal; column = 0;
	}
	else {
		nr_squares = 2 * n - 1 - diagonal;
		row = n - 1; column = diagonal + 1 - n;
	}
	for (int i = 0; i < nr_squares; i++, row--, column++) {
		square s(row, column);
		if (!is_attacking_position(s, diagonal, squares)) {
			squares[diagonal] = s;
			arrange_bishops(n, bishops - 1, diagonal + 2, squares, arrangements);
		}
	}
	if (bishops < (2 * n - 1) - diagonal) { // we can proceed withount putting a bishop in the current diagonal
		squares[diagonal] = square(-1, -1);
		arrange_bishops(n, bishops, diagonal + 2, squares, arrangements);
	}
}

int main(int /* argc */, char ** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	map< pair<int, int>, int> white_arrangements_cache, black_arrangements_cache;
	while (true) {
		int n, bishops;
		cin >> n >> bishops;
		if (!n && !bishops)
			break;
		int arrangements = 0;
		if (n) {
			for (int i = 0; i <= bishops; i++) {
				vector<square> white_squares(2 * n - 1, square(-1, -1)), black_squares(2 * n - 1, square(-1, -1));
					// squares[i] is the position of a square from the i-th diagonal, 
					// or (-1, -1) if any squares are not choosed from the i-th diagonal
				int white_arrangements = 0, black_arrangements = 0;
				map< pair<int, int>, int>::iterator j = white_arrangements_cache.find(make_pair(n, i));
				if (j != white_arrangements_cache.end())
					white_arrangements = j->second;
				else {
					arrange_bishops(n, i, 0, white_squares, white_arrangements);
					white_arrangements_cache.insert(make_pair(make_pair(n, i), white_arrangements));
				}
				map< pair<int, int>, int>::iterator k = black_arrangements_cache.find(make_pair(n, bishops - i));
				if (k != black_arrangements_cache.end())
					black_arrangements = k->second;
				else {
					arrange_bishops(n, bishops - i, 1, black_squares, black_arrangements);
					black_arrangements_cache.insert(make_pair(make_pair(n, bishops - i), black_arrangements));
				}
				arrangements += white_arrangements * black_arrangements;
			}
		}
		cout << arrangements << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

