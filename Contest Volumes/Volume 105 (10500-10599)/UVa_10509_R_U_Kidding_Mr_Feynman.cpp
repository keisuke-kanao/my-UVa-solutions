
/*
	UVa 10509 - R U Kidding Mr. Feynman?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10509_R_U_Kidding_Mr_Feynman.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	while (true) {
		double n;
		cin >> n;
		if (n == 0.0)
			break;
		double a = floor(pow(floor(n), 1.0 / 3.0));
		int dn = static_cast<int>(n), da = static_cast<int>(a);
		if (dn >= (da + 1) * (da + 1) * (da + 1))
			da++;
		a = static_cast<double>(da);
		double dx = (n - a * a * a) / (3.0 * a * a);
		cout << fixed << setprecision(4) << a + dx << endl;
	}
	return 0;
}

