
/*
	UVa 10550 - Combination Lock

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10550_Combination_Lock.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int calibrations = 40, degrees_per_calibration = 360 / 40;
	int first, second, third, fourth;
	while (cin >> first >> second >> third >> fourth) {
		if (!first && !second && !third && !fourth)
			break;
		int c = first - second;
		if (c < 0)
			c += calibrations;
		int d = third - second;
		if (d < 0)
			d += calibrations;
		c += d;
		d = third - fourth;
		if (d < 0)
			d += calibrations;
		c += d;
		cout << c * degrees_per_calibration + 360 * 3 << endl;
	}
	return 0;
}

