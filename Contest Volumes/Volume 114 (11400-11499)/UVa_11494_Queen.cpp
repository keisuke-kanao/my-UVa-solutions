
/*
	UVa 11494 - Queen

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11494_Queen.cpp
*/

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	while (true) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (!x1 && !y1 && !x2 && !y2)
			break;
		int nr_moves = 0;
		if (x1 == x2 && y1 == y2)
			;
		else if (abs(x1 - x2) == abs(y1 - y2)) // two are in diagonal positions
			nr_moves = 1;
		else {
			if (x1 != x2)
				nr_moves++;
			if (y1 != y2)
				nr_moves++;
		}
		cout << nr_moves << endl;
	}
	return 0;
}

