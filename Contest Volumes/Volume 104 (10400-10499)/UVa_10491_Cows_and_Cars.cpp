
/*
	UVa 10491 - Cows and Cars

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10491_Cows_and_Cars.cpp
*/

#include <cstdio>

int main()
{
	double ncows, ncars, nshow;
	while (scanf("%lf %lf %lf", &ncows, &ncars, &nshow) == 3) {
		double p = (ncows / (ncows + ncars)) * (ncars / ((ncows - nshow - 1.0) + ncars)) +
				// A cow (a door that hides a cow) was initially chosen, then a car was chosen after doors are revealed.
			(ncars / (ncows + ncars)) * ((ncars - 1.0) / ((ncows - nshow) + (ncars - 1.0)));
				// A car was initially chosen, then a car was chosen after doors are revealed.
		printf("%.5lf\n", p);
	}
	return 0;
}

