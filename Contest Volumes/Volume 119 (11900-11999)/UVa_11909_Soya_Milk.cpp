
/*
	UVa 11909 - Soya Milk

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11909_Soya_Milk.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	double l, w, h, theta;
	while (cin >> l >> w >> h >> theta) {
		double v, d = l * tan(theta * pi / 180.0);
		if (d < h)
			v = (h * 2.0 - d) * l * w / 2.0;
		else
			v = h * tan((90.0 - theta) * pi / 180.0) * h * w / 2.0;
		cout << fixed << setprecision(3) << v << " mL\n";
	}
	return 0;
}

