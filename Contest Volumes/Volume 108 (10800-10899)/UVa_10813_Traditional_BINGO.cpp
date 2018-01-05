
/*
	UVa 10813 - Traditional BINGO

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10813_Traditional_BINGO.cpp
*/

#include <iostream>
#include <utility>
using namespace std;

const int nr_rows = 5, nr_columns = 5, nr_numbers = 75;

bool is_bingo(int r, int c, int card[nr_rows][nr_columns])
{
	int ri, ci;
	for (ci = 0; ci < nr_columns; ci++)
		if (card[r][ci] != -1)
			break;
	if (ci == nr_columns)
		return true;
	for (ri = 0; ri < nr_rows; ri++)
		if (card[ri][c] != -1)
			break;
	if (ri == nr_rows)
		return true;
	if (r == c) {
		for (ri = 0; ri < nr_rows; ri++)
			if (card[ri][ri] != -1)
				break;
		if (ri == nr_rows)
			return true;
	}
	else if (r + c == nr_rows - 1) {
		for (ri = 0; ri < nr_rows; ri++)
			if (card[ri][nr_rows - ri - 1] != -1)
				break;
		if (ri == nr_rows)
			return true;
	}
	return false;
}

int main()
{
	int n, card[nr_rows][nr_columns];
	pair<int, int> map[nr_numbers + 1];
		// map[i] is the position of i in the card, or pair<int>(-1, -1) if i is not in the card
	cin >> n;
	while (n--) {
		int i, r, c;
		for (i = 1; i <= nr_numbers; i++)
			map[i] = make_pair(-1, -1);
		for (r = 0; r < nr_rows; r++)
			for (c = 0; c < nr_columns; c++) {
				if (r != 2 || c != 2) {
					cin >> card[r][c];
					map[card[r][c]] = make_pair(r, c);
				}
				else
					card[r][c] = -1; // free space
			}
		int bn, bi = -1;
		for (i = 0; i < nr_numbers; i++) {
			cin >> bn;
			if (bi == -1) {
				if (map[bn].first != -1) {
					r = map[bn].first; c = map[bn].second;
					card[r][c] = -1;
					if (is_bingo(r, c, card))
						bi = i + 1;
				}
			}
		}
		cout << "BINGO after " << bi << " numbers announced\n";
	}
	return 0;
}

