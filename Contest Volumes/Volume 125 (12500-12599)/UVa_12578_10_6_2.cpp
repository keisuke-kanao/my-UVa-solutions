
/*
	UVa 12578 - 10:6:2

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_12578_10_6_2.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = acos(-1.0);
	int t;
	cin >> t;
	while (t--) {
		double l;
		cin >> l;
		double red = pi * l * l * 0.04;
		double green = l * l * 0.6 - red;
		cout << fixed << setprecision(2) << red << ' ' << setprecision(2) << green << endl;
	}
	return 0;
}

