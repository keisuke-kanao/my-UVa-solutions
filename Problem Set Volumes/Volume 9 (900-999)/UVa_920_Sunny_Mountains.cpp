
/*
	UVa 920 - Sunny Mountains

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_920_Sunny_Mountains.cpp
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cmath>
using namespace std;

#define EPSILON numeric_limits<double>::epsilon()

struct point {
	double x, y;
};

struct line {
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term
};

void points_to_line(const point& p1, const point& p2, line& l)
{
	if (fabs(p1.x - p2.x) <= EPSILON) {
		l.a = 1; l.b = 0; l.c = -p1.x;
	}
	else {
		l.b = 1;
		l.a = -(p1.y - p2.y)/(p1.x - p2.x);
		l.c = -(l.a * p1.x) - l.b * p1.y;
	}
}

const int n_max = 100;
point points[n_max];

bool compare_point(const point& a, const point& b)
{
	return a.x > b.x;
}

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

int main()
{
	int c;
	cin >> c;
	while (c--) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		sort(points, points + n, compare_point); // sort the points in descending order of X-coordinate
		point p;
		line l;
		double mountainsides = 0.0;
		for (int i = 1, pi = 0; i < n; i++)
			if (points[i].y > points[pi].y) {
				points_to_line(points[i - 1], points[i], l);
				p.y = points[pi].y;
				p.x = (l.b * p.y + l.c) / (-l.a);
				mountainsides += euclidean_distance(p, points[i]);
				pi = i;
			}
		cout << fixed << setprecision(2) << mountainsides << endl;
	}
	return 0;
}


