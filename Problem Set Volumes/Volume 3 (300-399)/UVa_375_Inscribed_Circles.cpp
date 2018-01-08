
/*
	UVa 375 - Inscribed Circles and Isosceles Triangles

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_375_Inscribed_Circles.cpp
*/

/*
	For an isosceles triangle of base B and altitude H, the length of two isosceles sides s is:
		s^2 = H^2 + (B / 2)^2
	Then:
		s = sqrt(H^2 + B^2 / 4)
	For the radius r of the inscribed circlein the isosceles triangle:
		r = (2 * area) / (2 * s + B)
	where area = (1 / 2) * B * H, then:
		r = (B * H) / (2 * s + B)
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
using namespace std;

const double pi = 2.0 * acos(0.0);

double circumferences_of_inscribed_circles(double base, double altitude)
{
	const double min_radius = 0.000001;
	double circumferences = 0.0;
	while (true) {
		double side = sqrt(altitude * altitude + base * base / 4.0);
		double radius = (base * altitude) / (2.0 * side + base);
		if (radius < min_radius)
			break;
		circumferences += 2.0 * pi * radius;
		base = (base * (altitude - 2.0 * radius)) / altitude;
		altitude -= 2.0 * radius;
	}
	return circumferences;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		double base, altitude;
		cin >> base >> altitude;
		printf("%13.6lf\n", circumferences_of_inscribed_circles(base, altitude));
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

