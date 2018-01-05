
/*
	UVa 10316 - Airline Hub

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10316_Airline_Hub.cpp
*/

#include <cstdio>
#include <cmath>
#include <cfloat>

const double pi = 2.0 * acos(0.0);
const double sphere_radius  = 6378.0; // actually, 6378.137 km

const int n_max = 1000;

struct hub {
	double latitude_d_, longitude_d_; // in degrees
	double latitude_, longitude_; // in radian
} hubs[n_max];

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

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &hubs[i].latitude_d_, &hubs[i].longitude_d_);
			hubs[i].latitude_ = degree_to_radian(hubs[i].latitude_d_);
			hubs[i].longitude_ = degree_to_radian(hubs[i].longitude_d_);
		}
		double min_d = FLT_MAX;
		int min_i = 0;
		for (int i = 0; i < n; i++) {
			double max_d = FLT_MIN;
			for (int j = 0; j < n; j++)
				if (i != j) {
					double d = great_circle_distance(1.0, hubs[i].latitude_, hubs[i].longitude_, hubs[j].latitude_, hubs[j].longitude_);
					if (d > max_d)
						max_d = d;
				}
			if (max_d < min_d || fabs(max_d - min_d) < FLT_EPSILON) {
				min_d = max_d;
				min_i = i;
			}
		}
		printf("%.2lf %.2lf\n", hubs[min_i].latitude_d_, hubs[min_i].longitude_d_);
	}
	return 0;
}

