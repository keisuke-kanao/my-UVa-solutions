
/*
	UVa 10297 - Beavergnaw

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10297_Beavergnaw.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	while (true) {
		double D, V;
		cin >> D >> V;
		if (D == 0.0 && V == 0.0)
			break;
		double d = pow(D * D * D - (6.0 * V) / pi, 1.0 / 3.0);
		cout << fixed << setprecision(3) << d << endl;
	}
	return 0;
}

