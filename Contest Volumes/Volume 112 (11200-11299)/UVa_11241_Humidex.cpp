
/*
	UVa 11241 - Humidex

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11241_Humidex.cpp
*/

#include <cstdio>
#include <cmath>

int main()
{
	char s1[2], s2[2];
	double d1, d2;
	while (scanf("%s", s1) != EOF) {
		if (s1[0] == 'E')
			break;
		scanf("%lf %s %lf", &d1, s2, &d2);
		bool bh = false, bt = false, bd = false;
		double humedix, temparature, dewpoint;
		switch (s1[0]) {
		case 'H':
			bh = true; humedix = d1; break;
		case 'T':
			bt = true; temparature = d1; break;
		default:
			bd = true; dewpoint = d1; break;
		}
		switch (s2[0]) {
		case 'H':
			bh = true; humedix = d2; break;
		case 'T':
			bt = true; temparature = d2; break;
		default:
			bd = true; dewpoint = d2; break;
		}
		if (bt && bd)
			humedix = temparature + 0.5555 * (6.11 * exp(5417.7530 * (1.0 / 273.16 - 1.0 / (dewpoint + 273.16))) - 10.0);
		else if (bd && bh)
			temparature = humedix - 0.5555 * (6.11 * exp(5417.7530 * (1.0 / 273.16 - 1.0 / (dewpoint + 273.16))) - 10.0);
		else {
			double d = log((humedix - temparature + 5.555) / 3.394105 /* 0.5555 * 6.11 */);
			dewpoint = 74616.3856 /* 273.16^2 */ * d / (5417.7530 - 273.16 * d);
		}
		printf("T %.1lf D %.1lf H %.1lf\n", temparature, dewpoint, humedix);
	}
	return 0;
}

