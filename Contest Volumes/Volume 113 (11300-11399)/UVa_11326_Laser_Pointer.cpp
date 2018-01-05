
/*
	UVa 11326 - Laser Pointer

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_11326_Laser_Pointer.cpp
*/

#include <limits>
#include <cstdio>
#include <cmath> // C++11
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0);
	const double epsilon = numeric_limits<double>::epsilon();
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		double L, W, theta;
		scanf("%lf %lf %lf", &L, &W, &theta);
		double t = tan(theta * pi / 180.0), r = 1.0;
		if (t > W / L) {
			double x = W / t, y, A;
			int n = static_cast<int>(L / x + epsilon);
			if (n & 1) {
				y = (n + 1) * W - L * t;
				A = (n + 1) * hypot(x, W) - hypot((n + 1) * x - L, y);
			}
			else {
				y = L * t - W * n;
				A = hypot(x, W) * n + hypot(L - n * x, y);
			}
			r = A / hypot(L, y);
		}
		printf("%.3lf\n", r);
	}
	return 0;
}

