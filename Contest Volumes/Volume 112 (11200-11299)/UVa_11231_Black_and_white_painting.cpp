
/*
	UVa 11231 - Black and white painting

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11231_Black_and_white_painting.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	while (true) {
		int n, m, c;
		cin >> n >> m >> c;
		if (!n && !m && !c)
			break;
		int nr_cor, nr_cer; // number of chess boards in odd/even rows
		if (c) { // the corner is white
			nr_cor = (m - 6) / 2; nr_cer = (m - 7) / 2;
		}
		else {
			nr_cor = (m - 7) / 2; nr_cer = (m - 6) / 2;
		}
		int nr_or, nr_er; // number of odd/even rows
		nr_or = nr_er = (n - 7) / 2;
		if ((n - 7) % 2)
			nr_or++;
#ifdef DEBUG
		cout << nr_cor << ' ' << nr_cer << ' ' << nr_or << ' ' << nr_er << endl;
#endif
		cout << nr_cor * nr_or + nr_cer * nr_er << endl;
	}
	return 0;
}

