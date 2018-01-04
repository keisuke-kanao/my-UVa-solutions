
/*
	UVa 278 - Chess

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_278_Chess.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int p;
	cin >> p;
	while (p--) {
		char c;
		int m, n;
		cin >> c >> m >> n;
		int max_nr_pieces;
		switch (c) {
		case 'r': // Rook
			max_nr_pieces = min(m, n);
			break;
		case 'k': // Knight
			max_nr_pieces = (m * n + 1) / 2;
			break;
		case 'Q': // Queen
			max_nr_pieces = min(m, n);
			break;
		case 'K': // King
			max_nr_pieces = ((m + 1) / 2) * ((n + 1) / 2);
			break;
		}
		cout << max_nr_pieces << endl;
	}
	return 0;
}

