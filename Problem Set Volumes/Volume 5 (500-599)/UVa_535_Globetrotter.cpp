
/*
	UVa 535 - Globetrotter

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_535_Globetrotter.cpp

	from University of Ulm Local Contest 1997
		(http://www.informatik.uni-ulm.de/acm/Locals/1997/title97.html)
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

const double pi = 2.0 * acos(0.0);

const double sphere_radius  = 6378.0;
const int nr_cities_max = 100, nr_chars_max = 31;

struct city {
	char name_[nr_chars_max + 1];
	double latitude_, longitude_;
} cities[nr_cities_max + 1];

int compare_city(const void* i, const void* j)
{
	const city *ci = reinterpret_cast<const city*>(const_cast<void*>(i)), *cj = reinterpret_cast<const city*>(const_cast<void*>(j));
	return strcmp(ci->name_, cj->name_);
}

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
	int n = 0;
	while (true) {
		scanf("%s %lf %lf", cities[n].name_, &cities[n].latitude_, &cities[n].longitude_);
		if (!strcmp(cities[n].name_, "#"))
			break;
		cities[n].latitude_ = degree_to_radian(cities[n].latitude_);
		cities[n].longitude_ = degree_to_radian(cities[n].longitude_);
		n++;
	}
	qsort(cities, n, sizeof(city), compare_city);
	while (true) {
		city ca, cb;
		scanf("%s %s", ca.name_, cb.name_);
		if (!strcmp(ca.name_, "#") && !strcmp(cb.name_, "#"))
			break;
		city *pca = reinterpret_cast<city*>(bsearch(&ca, cities, n, sizeof(city), compare_city)),
			*pcb = reinterpret_cast<city*>(bsearch(&cb, cities, n, sizeof(city), compare_city));
		printf("%s - %s\n", ca.name_, cb.name_);
		if (!pca || !pcb)
			puts("Unknown");
		else
			printf("%.0lf km\n",
				great_circle_distance(sphere_radius, pca->latitude_, pca->longitude_, pcb->latitude_, pcb->longitude_));
	}
	return 0;
}

