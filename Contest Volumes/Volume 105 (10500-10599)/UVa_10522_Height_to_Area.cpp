
/*
	UVa 10522 - Height to Area

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10522_Height_to_Area.cpp
*/

/*
Denoting the altitudes from sides a, b, and c respectively as ha, hb, and hc, 
and denoting the semi-sum of the reciprocals of the altitudes as h = (1 / ha + 1 / hb + 1 / hc) / 2, 
the area T of the triangle is calculated as:
	1 / T = 4.0 * sqrt(h * (h - 1 / ha) * (h - 1 / hb) * (h - 1 / hc)).
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

int main()
{
	const double epsilon = numeric_limits<double>::epsilon();
	int n;
	cin >> n;
	do {
		double ha, hb, hc;
		cin >> ha >> hb >> hc;
		double h = (1.0 / ha + 1.0 / hb + 1.0 / hc) / 2.0;
		double d = h * (h - 1.0 / ha) * (h - 1.0 / hb) * (h - 1.0 / hc);
		if (ha > epsilon && hb > epsilon && hc > epsilon && d > epsilon) {
			double t = 4.0 * sqrt(d);
			cout << fixed << setprecision(3) << 1.0 / t << endl;
		}
		else {
			cout << "These are invalid inputs!\n";
			n--;
		}
	} while (n);
	return 0;
}

