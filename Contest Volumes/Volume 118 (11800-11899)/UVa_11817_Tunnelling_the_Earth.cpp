
/*
	UVa 11817 - Tunnelling the Earth

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11817_Tunnelling_the_Earth.cpp
*/

#include <cstdio>
#include <cmath>

const double pi = 2.0 * acos(0.0);

const double sphere_radius  = 6371009.0;

double degree_to_radian(double degree)
{
	return (pi / 180.0) * degree;
}

#if 0
double central_angle(double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
/*
  latitude_s/_f and longitude_s/_f are in units of radian (radian = (pi / 180) * degree)
*/
	double lambda = longitude_f - longitude_s;
	double delta = acos(sin(latitude_s) * sin(latitude_f) + cos(latitude_s) * cos(latitude_f) * cos(lambda));
	return delta;
}
#else
double central_angle(double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
/*
  latitude_s/_f and longitude_s/_f are in units of radian (radian = (pi / 180) * degree)
*/
	double phi = latitude_f - latitude_s, lambda = longitude_f - longitude_s;
	double delta = pow(sin(phi / 2.0), 2) + cos(latitude_s) * cos(latitude_f) * pow(sin(lambda / 2.0), 2);
	return 2.0 * asin(sqrt(delta));
}
#endif

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		double latitude_s, longitude_s, latitude_f, longitude_f;
		scanf("%lf %lf %lf %lf", &latitude_s, &longitude_s, &latitude_f, &longitude_f);
		double delta = central_angle(degree_to_radian(latitude_s), degree_to_radian(longitude_s),
			degree_to_radian(latitude_f), degree_to_radian(longitude_f));
		double distance = sphere_radius * delta - 2.0 * sphere_radius * sin(delta / 2.0);
		printf("%.0lf\n", distance);
	}
	return 0;
}

