
/*
	UVa 10287 - Gifts in a Hexagonal Box

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10287_Gifts_in_a_Hexagonal_Box.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double c1 = sqrt(3.0) / 2.0, c2 = sqrt(3.0) / (2.0 + sqrt(3.0)),
		c3 = sqrt(3.0) / 4.0, c4 = (6.0 * sqrt(21.0) - 21.0) / (10.0 * sqrt(3.0));
	double s;
	while (cin >> s)
		cout << fixed << setprecision(10) << c1 * s << ' ' << setprecision(10) << c2 * s << ' ' <<
			setprecision(10) << c3 * s << ' ' << setprecision(10) << c4 * s << endl;
	return 0;
}

