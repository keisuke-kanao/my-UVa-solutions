
/*
	UVa 10693 - Traffic Volume

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10693_Traffic_Volume.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	while (true) {
		double l, f;
		cin >> l >> f;
		if (l == 0.0 && f == 0.0)
			break;
		double v = sqrt(2.0 * l * f);
		double volume = v * 3600.0 / (2.0 * l);
		cout << fixed << setprecision(8) << v << ' ' << volume << endl;
	}
	return 0;
}

