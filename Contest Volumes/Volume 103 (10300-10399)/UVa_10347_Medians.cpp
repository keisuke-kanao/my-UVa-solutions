
/*
	UVa 10347 - Medians

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10347_Medians.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/*
	The area of a triangle can be expressed in terms of the medians by:
		area = (4 / 3) * sqrt(s * (s - m1) * (s - m2) * (s - m3))
	where
		s = (1 / 2)(m1 + m2 + m3)
*/

int main()
{
	double m1, m2, m3;
	while (cin >> m1 >> m2 >> m3) {
		double s = (m1 + m2 + m3) / 2.0;
		double as = s * (s - m1) * (s - m2) * (s - m3);
		double a = (as > 0.0) ? (sqrt(as) * 4.0) / 3.0 : -1.0;
		cout << fixed << setprecision(3) << a << endl;
	}
}

