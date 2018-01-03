
/*
	UVa 815 - Flooded!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_815_Flooded.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

int main()
{
	const int n_max = 30, m_max = 30, nr_elevations_max = n_max * m_max;
	const double epsilon = numeric_limits<double>::epsilon(), square_area = 10.0 * 10.0;
	for (int r = 1; ; r++) {
		int m, n;
		scanf("%d %d", &m, &n);
		if (!m)
			break;
		int i, nr_elevations = m * n, elevations[nr_elevations_max];
		double water;
		for (i = 0; i < nr_elevations; i++)
			scanf("%d", &elevations[i]);
		scanf("%lf", &water);
		printf("Region %d\n", r);
		sort(elevations, elevations + nr_elevations);
		double height = elevations[0];
		if (water) {
			double area = square_area;
			for (i = 0; i < nr_elevations - 1; i++, area += square_area) {
				double h = elevations[i + 1] - elevations[i], v = area * h;
				if (v - water >= epsilon) { // v >= water
					h = water / area;
					height += h;
					water = 0.0;
					break;
				}
				else {
					height = elevations[i + 1];
					water -= v;
				}
#ifdef DEBUG
				printf("%.2lf %.2lf\n", height, water);
#endif
			}
			if (water > epsilon)
				height += water / area;
		}
		else
			i = -1;
		printf("Water level is %.2lf meters.\n", height);
		printf("%.2lf percent of the region is under water.\n\n", static_cast<double>(i + 1) * 100.0 / nr_elevations);
	}
	return 0;
}

