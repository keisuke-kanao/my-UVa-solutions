
/*
	UVa 167 - The Sultan's Successors

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_167_The_Sultans_Successors.cpp

	from ACM South Pacific Regionals 1991 Problem D
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1991/index.html)
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int nr_rows = 8, nr_columns = 8;

int get_columns(int ri, const int queens[nr_rows], int columns[nr_columns])
{
	int c = 0;
	for (int i = 0; i < nr_columns; i++) {
		int j;
		for (j = 0 ; j < ri; j++)
			if (abs(ri - j) == abs(i - queens[j]) || // diagonal threat
				i == queens[j]) // column threat
				break;
		if (j == ri) // no threat
			columns[c++] = i;
	}
	return c;
}

void eight_queen(int ri, int queens[nr_rows], const int squares[nr_rows][nr_columns], int& max_score)
{
	if (ri == nr_rows) {
		int score = 0;
		for (int i = 0; i < nr_rows; i++)
			score += squares[i][queens[i]];
		if (score > max_score)
			max_score = score;
	}
	else {
		int columns[nr_columns];
		int c = get_columns(ri, queens, columns);
		for (int i = 0; i < c; i++) {
			queens[ri] = columns[i];
			eight_queen(ri + 1, queens, squares, max_score);
		}
	}
}

int main()
{
	int k;
	cin >> k;
	while (k--) {
		int squares[nr_rows][nr_columns];
		for (int i = 0; i < nr_rows; i++)
			for (int j = 0; j < nr_columns; j++)
				cin >> squares[i][j];
		int max_score = 0;
		int queens[nr_columns];
		eight_queen(0, queens, squares, max_score);
		cout << setfill(' ') << setw(5) << max_score << endl;
	}
	return 0;
}

