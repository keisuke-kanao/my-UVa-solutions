
/*
	UVa 10286 - Trouble with a Pentagon

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10286_Trouble_with_a_Pentagon.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/*
	side of a square = (side of the pentagon) * sin(108 degree) / sin (63 degree).
	See squre.pdf.
*/

int main()
{
	const double pi = 2.0 * acos(0.0); // 3.14159265358979323846
	const double sin_108 = sin((pi * 108.0) / 180.0), sin_63 = sin((pi * 63.0) / 180.0);
	double s;
	while (cin >> s)
		cout << fixed << setprecision(10) << (s * sin_108) / sin_63 << endl;
	return 0;
}

