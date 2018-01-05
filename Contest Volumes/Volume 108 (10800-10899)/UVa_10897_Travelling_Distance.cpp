
/*
	UVa 10897 - Travelling Distance

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10897_Travelling_Distance.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

const double pi = 2.0 * acos(0.0);
const double sphere_radius  = 6371.01;

double degree_to_radian(double degree)
{
	return (pi / 180.0) * degree;
}

#if 0
double great_circle_distance(double radius, double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
/*
  latitude_s/_f and longitude_s/_f are in units of radian (radian = (pi / 180) * degree)
*/
  double lambda = longitude_f - longitude_s;
  double delta = acos(sin(latitude_s) * sin(latitude_f) + cos(latitude_s) * cos(latitude_f) * cos(lambda));
  return radius * delta;
}
#else
double great_circle_distance(double radius, double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
/*
  latitude_s/_f and longitude_s/_f are in units of radian (radian = (pi / 180) * degree)
*/
  double phi = latitude_f - latitude_s, lambda = longitude_f - longitude_s;
  double delta = pow(sin(phi / 2.0), 2) + cos(latitude_s) * cos(latitude_f) * pow(sin(lambda / 2.0), 2);
  delta = 2 * asin(sqrt(delta));
  return radius * delta;
}
#endif

void read_location(double& latitude, double& longitude)
{
	double a, b, c, d, e, f;
	char X[2], Y[2];
	scanf("%lf %lf %lf %s %lf %lf %lf %s", &a, &b, &c, X, &d, &e, &f, Y);
	latitude = a + b / 60.0 + c / 3600.0, longitude = d + e / 60.0 + f / 3600.0;
	if (X[0] == 'S')
		latitude = -latitude;
	if (Y[0] == 'W')
		longitude = -longitude;
	latitude = degree_to_radian(latitude);
	longitude = degree_to_radian(longitude);
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		double latitude_s, longitude_s, latitude_f, longitude_f;
		read_location(latitude_s, longitude_s);
		read_location(latitude_f, longitude_f);
		printf("%.2lf\n",
			great_circle_distance(sphere_radius, latitude_s, longitude_s, latitude_f, longitude_f));
	}
	return 0;
}

