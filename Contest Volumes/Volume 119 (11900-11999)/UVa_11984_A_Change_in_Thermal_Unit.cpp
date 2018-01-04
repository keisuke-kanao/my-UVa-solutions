
/*
	UVa 11984 - A Change in Thermal Unit

	To build using Visual Studio 2008:
		cl -EHsc UVa_11984_A_Change_in_Thermal_Unit.cpp
*/

#include <cstdio>

int main()
{
	int t;
	scanf("%d", &t);
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		double c, d;
		scanf("%lf %lf", &c, &d);
		printf("Case %d: %.2lf\n", case_nr, c + d * 5.0 / 9.0);
	}
	return 0;
}

