
/*
	UVa 10678 - The Grazing Cow

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10678_The_Grazing_Cow.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	int N;
	cin >> N;
	while (N--) {
		double D, L;
		cin >> D >> L;
		// area is an ellipse whose major and minor axies are (L / 2) and (sqrt(L * L - D * D) / 2)
		double area = pi * L * sqrt(L * L - D * D) / 4.0;
		cout << fixed << setprecision(3) << area << endl;
	}
	return 0;
}

