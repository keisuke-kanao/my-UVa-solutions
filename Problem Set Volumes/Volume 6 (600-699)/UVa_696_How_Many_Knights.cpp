
/*
	UVa 696 - How Many Knights

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_696_How_Many_Knights.cpp

	This problem is similar to Uva 278 - Chess.
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	while (true) {
		int m, n;
		cin >> m >> n;
		if (!m && !n)
			break;
		int r = m, c = n;
		if (m > n)
			swap(m, n);
		int max_nr_pieces;
		if (!m)
			max_nr_pieces = 0;
		else if (m == 1)
			max_nr_pieces = n;
		else if (m == 2) {
			max_nr_pieces = ((n + 3) / 4) * 4;
			if ((n % 4) == 1)
				max_nr_pieces -= 2;
		}
		else
			max_nr_pieces = (m * n + 1) / 2;
		cout << max_nr_pieces << " knights may be placed on a " << r << " row " << c << " column board.\n";
	}
	return 0;
}

