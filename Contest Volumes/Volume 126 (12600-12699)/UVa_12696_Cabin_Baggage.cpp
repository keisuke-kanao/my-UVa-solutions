
/*
	UVa 12696 - Cabin Baggage

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12696_Cabin_Baggage.cpp
*/

#include <cstdio>

int main()
{
	const double length_max = 56.0, width_max = 45.0, depth_max = 25.0, all_sides_max = 125.0,
		weight_max = 7.0;
	int t;
	scanf("%d", &t);
	int nr_allowed = 0;
	while (t--) {
		double length, width, depth, weight;
		scanf("%lf %lf %lf %lf", &length, &width, &depth, &weight);
		if ((length <= length_max && width <= width_max && depth <= depth_max || length + width + depth <= all_sides_max) &&
			weight <= weight_max) {
			puts("1");
			nr_allowed++;
		}
		else
			puts("0");
	}
	printf("%d\n", nr_allowed);
	return 0;
}

