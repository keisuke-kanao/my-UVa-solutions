
/*
	UVa 10283 - The Kissing Circles

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10283_The_Kissing_Circles.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	double R;
	int N;
	while (cin >> R >> N) {
		double r, I, E;
		if (N > 1) {
			double a = pi / N;
			r = R * sin(a) / (1.0 + sin(a));
			I = r * r * (cos(a) * N / sin(a) - pi * (N - 2) / 2.0);
			E = pi * R * R - (I + pi * r * r * N);
		}
		else {
			r = R;
			I = E = 0.0;
		}
		cout << fixed << setprecision(10) << r << ' ' <<
			setprecision(10) << I << ' ' << setprecision(10) << E << endl;
	}
	return 0;
}

