
/*
	UVa 410 - Station Balance

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_410_Station_Balance.cpp

	from ACM South Central Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1996/index.html)

	An accepted solution.
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>

int compare_mass(const void* i, const void* j)
{
	return *reinterpret_cast<const int*>(i) - *reinterpret_cast<const int*>(j);
}

int main()
{
	const int nr_specimens_max = 10;
	int masses[nr_specimens_max]; // masses[i] is the mass of i-th specimen
	int c, s;
	for (int sn = 1; scanf("%d %d", &c, &s) != EOF; sn++) {
		double average_mass = 0.0, imbalance = 0.0;
		for (int i = 0; i < s; i++) {
			scanf("%d", &masses[i]);
			average_mass += masses[i];
		}
		average_mass /= c;
		printf("Set #%d\n", sn);
		int cx2 = c * 2;
		for (int i = s; i < cx2; i++)
			masses[i] = 0;
		qsort(masses, cx2, sizeof(int), compare_mass);
		for (int i = 0; i < c; i++) {
	        printf("% d:", i);
			if (masses[i])
				printf(" %d", masses[i]);
			if (masses[cx2 - i - 1])
				printf(" %d", masses[cx2 - i - 1]);
			putchar('\n');
			imbalance += fabs(masses[i] + masses[cx2 - i - 1] - average_mass);
		}
		printf("IMBALANCE = %0.5lf\n\n", imbalance);
	}
	return 0;
}

