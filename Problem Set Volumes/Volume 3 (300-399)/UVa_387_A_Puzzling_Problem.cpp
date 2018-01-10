
/*
	UVa 387 - A Puzzling Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_387_A_Puzzling_Problem.cpp

	from ACM Mid-Central Region 1995 Regional Programming Contest Problem #3
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1995/index.html)
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*
	A piece is represented by 16 bits where 
	i-th bit (0 <= i < 16) is set if there is a solid shape at row of (i / 4)  and column of (i % 4).

	Sort the pieces by descending order of the number of solid shapes they have and then 
	backtrack by trying to place a piece at a free area in the square in turn.
*/

const int nr_pieces_max = 5;
const int nr_rows_max = 4, nr_columns_max = 4;

struct piece {
	int nr_;
	int nr_rows_, nr_columns_;
	int nr_solid_shapes_;
	unsigned int shape_;
	bool operator<(const piece& p) const {return nr_solid_shapes_ > p.nr_solid_shapes_;}
};

int nr_pieces;
piece pieces[nr_pieces_max];
unsigned long long square;
	// bit (4 * i) - bit (4 * i + 3) is the piece # that is placed at at row of (i / 4)  and column of (i % 4).

void set_square(int pn, unsigned int shape)
{
	const unsigned long long mask = 0x0f;
	for (int i = 0; i < nr_rows_max * nr_columns_max; i++, shape >>= 1)
		if (shape & 1) {
			square &= ~(mask << (i * 4));
			square |= static_cast<long long>(pn) << (i * 4);
		}
}

void print_square()
{
	for (int i = 0; i < nr_rows_max; i++) {
		for (int j = 0; j < nr_columns_max; j++, square >>= 4)
			cout << static_cast<char>('1' + (square & 0x0f));
		cout << endl;
	}
}

bool form_square(int pi, unsigned int s)
{
	if (pi == nr_pieces)
		return s == 0xffff;
	else {
		piece& p = pieces[pi];
		unsigned int shape = p.shape_;
		for (int i = 0; i <= nr_rows_max - p.nr_rows_; i++, shape <<= 4) { // move down a piece
			unsigned int sh = shape;
			for (int j = 0; j <= nr_columns_max - p.nr_columns_; j++, sh <<= 1) // move a piece to left
				if (!(s & sh)) { // a piece is placeable
					set_square(p.nr_, sh);
					if (form_square(pi + 1, s | sh))
						return true;
				}
		}
	}
	return false;
}

int main()
{
	for (int nr_puzzles = 0; ; nr_puzzles++) {
		cin >> nr_pieces;
		if (!nr_pieces)
			break;
		if (nr_puzzles)
			cout << endl;
		memset(pieces, 0, sizeof(pieces));
		int nr_shapes = 0;
		for (int i = 0; i < nr_pieces; i++) {
			piece& p = pieces[i];
			p.nr_ = i;
			cin >> p.nr_rows_ >> p.nr_columns_;
			for (int j = 0; j < p.nr_rows_; j++)
				for (int k = 0; k < p.nr_columns_; k++) {
					char s;
					cin >> s;
					if (s == '1') {
						p.nr_solid_shapes_++;
						p.shape_ |= 1 << (j * nr_rows_max + k);
					}
				}
			nr_shapes += p.nr_solid_shapes_;
		}
		bool successful = false;
/*
		if (nr_shapes == nr_rows_max * nr_columns_max) {
*/
			sort(pieces, pieces + nr_pieces);
			square = 0;
			successful = form_square(0, 0);
/*
		}
*/
		if (successful)
			print_square();
		else
			cout << "No solution possible\n";
	}
	return 0;
}

