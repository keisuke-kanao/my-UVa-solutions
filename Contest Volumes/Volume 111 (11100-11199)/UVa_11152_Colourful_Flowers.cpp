
/*
	UVa 11152 - Colourful Flowers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11152_Colourful_Flowers.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	double a, b, c;
	while (cin >> a >> b >> c) {
		double s = (a + b + c) / 2.0;
		double triangle_area = sqrt(s * (s - a) * (s - b) * (s - c));
		double circumcircle_r = a * b * c / (4.0 * triangle_area);
		double circumcircle_area = pi * circumcircle_r * circumcircle_r;
		double incircle_r = sqrt((s - a) * (s - b) * (s - c) / s);
		double incircle_area = pi * incircle_r * incircle_r;
		cout << fixed << setprecision(4) << circumcircle_area - triangle_area << ' ' <<
			triangle_area - incircle_area << ' ' << incircle_area << endl;
	}
	return 0;
}

