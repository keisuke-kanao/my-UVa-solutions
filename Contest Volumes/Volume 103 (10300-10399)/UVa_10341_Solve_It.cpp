
/*
	UVa 10341 - Solve It

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10341_Solve_It.cpp

	An accepted soluiton.
*/

#include <iostream>
#include <cstdio>
#include <cfloat>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

/*
	All of the functions that make up the equation monotonically increase/decrease for 0 <= x <= 1.0.
*/

#define EPSILON FLT_EPSILON

double p, q, r, s, t, u;

double calculate_equation(double x)
{
	return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

double solve_equation()
{
	const double epsilon = 1.0e-7;
	double l = 0.0, h = 1.0;
	double lr = calculate_equation(l);
	if (fabs(lr) <= epsilon)
		return l;
	double hr = calculate_equation(h);
	if (fabs(hr) <= epsilon)
		return h;
	if (lr > EPSILON && hr > EPSILON || lr < -EPSILON && hr < -EPSILON)
		return -1;
	double m = (l + h) / 2.0;
	for ( ; h - l > EPSILON; m = (l + h) /  2.0) {
		double mr = calculate_equation(m);
		if (fabs(mr) <= epsilon)
			break;
		if (lr < hr) { // for monotonically increasing functions
			if (mr > EPSILON) {
				h = m; hr = mr;
			}
			else {
				l = m; lr = mr;
			}
		}
		else { // for monotonically decreasing functions
			if (mr > EPSILON) {
				l = m; lr = mr;
			}
			else {
				h = m; hr = mr;
			}
		}
	}
	return m;
}

int main()
{
	while (cin >> p >> q >> r >> s >> t >> u) {
		double x = solve_equation();
		if (x < 0.0)
			printf("No solution\n");
		else
			printf("%.4lf\n", x);
	}
	return 0;
}

