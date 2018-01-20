
/*
	12.6.3 Star
	PC/UVa IDs: 111203/10159, Popularity: C, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10159_Star.cpp
*/

/*
	Define a triangular coordinates that is made up of row, column, and diagonal axes.
	Represent each triangular cell by a three set of triangular coordinates.

	struct tr_cell {
		int r; // horizontal "row" axis
		int c; // "column" axis, 60 degrees from horizontal
		int d; // "diagonal" axis, 120 degrees from horizontal
	};

	A, B, C, and D lines are represented by their row coordinate values.
	E, F, G, and H lines are represented by their column coordinate vlaues.
	I, J, K, and L lines are represented by their diagonal coordinate values.

	Each cell's possible maximum digit is calculated by taking the minimum value of the two or three 
	lines to which the cell belongs.

	The smallest possbile sum is calculated by choosing the smallest set of cells each of which is a "representative" 
	of at least one line to which it belongs.
	A representative cell has the same maximum possible value as the one for at least one of the lines (rows, columns, 
	and diagonals) it belongs to. In other words, one cell is a representative for at most three lines (one row, one 
	column, and one diagonal).
*/

#include <algorithm>
#include <iostream>
#ifdef DEBUG
#include <iomanip>
#endif
#include <vector>
#include <climits>
using namespace std;

struct tr_cell {
	int r; // horizontal "row" axis
	int c; // "column" axis, 60 degrees from horizontal
	int d; // "diagonal" axis, 120 degrees from horizontal
	int digit_min, digit_max;

	tr_cell(int _r, int _c, int _d) : r(_r), c(_c), d(_d), digit_min(0), digit_max(INT_MAX) {}
	tr_cell(const tr_cell& tc) : r(tc.r), c(tc.c), d(tc.d), digit_min(0), digit_max(INT_MAX) {}
};

struct tr_line {
	int r_c_d; // row or column or diagonal coordinate
	int digit; // largest digit
	bool represented; // if true, the line has been represented by one of the cells that belong to the line

	tr_line(int _r_c_d, int _digit) : r_c_d(_r_c_d), digit(_digit), represented(false) {}
};

#ifdef DEBUG
ostream& operator<<(ostream& os, const tr_cell& tc)
{
	os << setfill(' ') << '(' << setw(2) << tc.r << ", " << setw(2) << tc.c << ", " << setw(2) << tc.d << ')';
	os << tc.digit_min << ' ' << tc.digit_max;
	return os;
}
#endif

const int nr_rows = 4, nr_columns = 4, nr_diagonals = 4;
const int nr_lines = nr_rows + nr_columns + nr_diagonals;

int read_line_digits(vector<tr_line>& tr_lines)
{
	int i = 0;
	for (int r = 1; i < nr_rows; i++, r--) {
		int digit;
		if (cin >> digit)
			tr_lines.push_back(tr_line(r, digit));
		else
			return i;
	}
	for (int c = -2; i < nr_rows + nr_columns; i++, c++) {
		int digit;
		if (cin >> digit)
			tr_lines.push_back(tr_line(c, digit));
		else
			return i;
	}
	for (int d = -2; i < nr_lines; i++, d++) {
		int digit;
		if (cin >> digit)
			tr_lines.push_back(tr_line(d, digit));
		else
			return i;
	}
	return i;
}

void generate_tr_cells(vector<tr_cell>& tr_cells)
{
	const tr_cell cells[] = {
		tr_cell( 3, -2,  1),
		tr_cell( 2, -2,  0), tr_cell( 2, -2,  1), tr_cell( 2, -1,  1),
		tr_cell( 1, -4, -2), tr_cell( 1, -3, -2), tr_cell( 1, -3, -1), tr_cell( 1, -2, -1),
		tr_cell( 1, -2,  0), tr_cell( 1, -1,  0), tr_cell( 1, -1,  1), tr_cell( 1,  0,  1),
		tr_cell( 1,  0,  2), tr_cell( 1,  1,  2), tr_cell( 1,  1,  3),
		tr_cell( 0, -3, -2), tr_cell( 0, -2, -2), tr_cell( 0, -2, -1), tr_cell( 0, -1, -1),
		tr_cell( 0, -1,  0), tr_cell( 0,  0,  0), tr_cell( 0,  0,  1), tr_cell( 0,  1,  1),
		tr_cell( 0,  1,  2),
		tr_cell(-1, -2, -3), tr_cell(-1, -2, -2), tr_cell(-1, -1, -2), tr_cell(-1, -1, -1),
		tr_cell(-1,  0, -1), tr_cell(-1,  0,  0), tr_cell(-1,  1,  0), tr_cell(-1,  1,  1),
		tr_cell(-1,  2,  1),
		tr_cell(-2, -2, -4), tr_cell(-2, -2, -3), tr_cell(-2, -1, -3), tr_cell(-2, -1, -2),
		tr_cell(-2,  0, -2), tr_cell(-2,  0, -1), tr_cell(-2,  1, -1), tr_cell(-2,  1,  0),
		tr_cell(-2,  2,  0), tr_cell(-2,  2,  1), tr_cell(-2,  3,  1),
		tr_cell(-3,  0, -2), tr_cell(-3,  1, -2), tr_cell(-3,  1, -1),
		tr_cell(-4,  1, -2)
	};
	for (size_t i = 0; i < sizeof(cells) / sizeof(tr_cell); i++)
		tr_cells.push_back(cells[i]);
}

void set_possible_max_digits(const vector<tr_line>& tr_lines, vector<tr_cell>& tr_cells)
{
	for (int i = 0; i < nr_lines; i++) {
		const tr_line& line = tr_lines[i];
		for (vector<tr_cell>::iterator tc = tr_cells.begin(); tc != tr_cells.end(); tc++)
			if (i < nr_rows && tc->r == line.r_c_d ||
				i >= nr_rows && i < nr_rows + nr_columns && tc->c == line.r_c_d ||
				i >= nr_rows + nr_columns && tc->d == line.r_c_d)
				tc->digit_max = min(tc->digit_max, line.digit);
	}
}

int find_other_lines(vector<tr_line>& tr_lines, const tr_cell& cell, int digit, int& rl, int& cl, int& dl)
// find other lines that have the same largest digit and have not been represented
{
	int nr_represented = 0;
	rl = cl = dl = INT_MAX;
	for (int i = 0; i < nr_rows; i++)
		if (tr_lines[i].r_c_d == cell.r && tr_lines[i].digit == digit && !tr_lines[i].represented) {
			nr_represented++; rl = i; break;
		}
	for (int i = nr_rows; i < nr_rows + nr_columns; i++)
		if (tr_lines[i].r_c_d == cell.c && tr_lines[i].digit == digit && !tr_lines[i].represented) {
			nr_represented++; cl = i; break;
		}
	for (int i = nr_rows + nr_columns; i < nr_lines; i++)
		if (tr_lines[i].r_c_d == cell.d && tr_lines[i].digit == digit && !tr_lines[i].represented) {
			nr_represented++; dl = i; break;
		}
	return nr_represented;
}

int set_possible_min_digits(vector<tr_line>& tr_lines, vector<tr_cell>& tr_cells)
{
	int min_digits = 0;
	for (int i = 0; i < nr_lines; i++) {
		tr_line& line = tr_lines[i];
		if (line.represented) // a representative cell for the line has already been selected
			continue;
		if (!line.digit)
			continue;
		int maxs = 0, represented = 0, representative, row_line, column_line, diagonal_line, r, rl, cl, dl;
		for (int j = 0; j < tr_cells.size(); j++) { // collect the cells that belong to the line
			tr_cell& cell = tr_cells[j];
			if ((i < nr_rows && cell.r == line.r_c_d ||
				i >= nr_rows && i < nr_rows + nr_columns && cell.c == line.r_c_d ||
				i >= nr_rows + nr_columns && cell.d == line.r_c_d) && cell.digit_max == line.digit) {
				// cell has the same maximum possible value as the one for the line it belongs to
				maxs++;
				if ((r = find_other_lines(tr_lines, cell, line.digit, rl, cl, dl)) > represented) {
					// one cell is a representative for at most three lines
					representative = j;
					represented = r; row_line = rl; column_line = cl; diagonal_line = dl;
					if (represented == 3)
						break;
				}
			}
		}
		if (!maxs)
			return -1;
		else {
			min_digits++;
			tr_cells[representative].digit_min = tr_cells[representative].digit_max;
			if (row_line != INT_MAX)
				tr_lines[row_line].represented = true;
			if (column_line != INT_MAX)
				tr_lines[column_line].represented = true;
			if (diagonal_line != INT_MAX)
				tr_lines[diagonal_line].represented = true;
		}
	}
	return min_digits;
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		vector<tr_line> tr_lines;
		if (read_line_digits(tr_lines) < nr_lines)
			break;
		vector<tr_cell> tr_cells;
		generate_tr_cells(tr_cells);
		// set the possible max. digits of the cells
		set_possible_max_digits(tr_lines, tr_cells);
#ifdef DEBUG
		for (vector<tr_cell>::const_iterator i = tr_cells.begin(); i != tr_cells.end(); i++)
			cout << *i << endl;
		cout << endl;
#endif
		// choose "representative" cells to calculate the possible min. sum
		int min_digits = set_possible_min_digits(tr_lines, tr_cells);
#ifdef DEBUG
		for (vector<tr_cell>::const_iterator i = tr_cells.begin(); i != tr_cells.end(); i++)
			cout << *i << endl;
		cout << endl;
#endif
		if (min_digits == -1)
			cout << "NO SOLUTION\n";
		else {
			// calculate the possible min. and max. sums
			int min_sum = 0, max_sum = 0;
			for (vector<tr_cell>::iterator tc = tr_cells.begin(); tc != tr_cells.end(); tc++) {
				min_sum += tc->digit_min; max_sum += tc->digit_max;
			}
			cout << min_sum << ' ' << max_sum << endl;
		}
	}
	return 0;
}

