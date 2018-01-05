
/*
	UVa 10991 - Region

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10991_Region.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	int k;
	cin >> k;
	while (k--) {
		double r1, r2, r3;
		cin >> r1 >> r2 >> r3;
		double a = r2 + r3, b = r3 + r1, c = r1 + r2; // sides of the triangle
		double s = r1 + r2 + r3; // (a + b + c) / 2.0
		double area = sqrt(s * (s - a) * (s - b) * (s - c)); // area of the triangle
		double A = acos((b * b + c * c - a * a) / (2.0 * b * c)), // from the law of cosines
			B = acos((c * c + a * a - b * b) / (2.0 * c * a)), C = acos((a * a + b * b - c * c) / (2.0 * a * b));
		double g = area - (r1 * r1 * A + r2 * r2 * B + r3 * r3 * C) / 2.0;
		cout << fixed << setprecision(6) << g << endl;
	}
	return 0;
}

