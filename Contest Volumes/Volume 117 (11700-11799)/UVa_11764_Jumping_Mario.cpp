
/*
	UVa 11764 - Jumping Mario

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11764_Jumping_Mario.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n;
		cin >> n;
		int height;
		cin >> height;
		n--;
		int nr_high_jumps = 0, nr_low_jumps = 0;
		while (n--) {
			int h;
			cin >> h;
			if (h > height)
				nr_high_jumps++;
			else if (h < height)
				nr_low_jumps++;
			height = h;
		}
		cout << "Case " << case_nr << ": " << nr_high_jumps << ' ' << nr_low_jumps << endl;
	}
	return 0;
}

