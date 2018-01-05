
/*
	UVa 10668 - Expanding Rods

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10668_Expanding_Rods.cpp
*/

#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
	const double pi = 2.0 * acos(0.0), epsilon = numeric_limits<double>::epsilon();
	while (true) {
		double l, n, c;
		scanf("%lf %lf %lf", &l, &n, &c);
		if (l < 0.0 && n < 0.0 && c < 0.0)
			break;
		if (l < epsilon || n < epsilon || c < epsilon) {
			printf("%.3lf\n", 0.0);
			continue;
		}
		double nl = (1.0 + n * c) * l, mid;
		for (double low = 0.0, high = pi / 2.0; low - high < epsilon; ) {
			mid = (low + high) / 2.0;
#ifdef DEBUG
			printf("%.15lf %.15lf %.15lf\n", low, mid, high);
#endif
			double result = nl / mid - l / sin(mid);
			if (result > epsilon)
				low = mid;
			else if (result < -epsilon)
				high = mid;
			else
				break;
		}
		double r = nl / (mid * 2.0), d = r * (1.0 - cos(mid));
		printf("%.3lf\n", d);
	}
	return 0;
}

