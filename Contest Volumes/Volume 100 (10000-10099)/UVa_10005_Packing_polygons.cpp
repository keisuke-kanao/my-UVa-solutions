
/*
	UVa 10005 - Packing polygons

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10005_Packing_polygons.cpp
*/

#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

const double epsilon = numeric_limits<float>::epsilon();
const int n_max = 100;

struct point {
	double x, y;
} points[n_max];

double square_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

int compare_double(double d1, double d2)
{
	double d = d1 - d2;
	if (fabs(d) < epsilon)
		return 0;
	else if (d > 0.0)
		return 1;
	else
		return -1;
}

bool pack_polygon(int n, double R)
{
	double sR = R * R;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++) {
			double sr = square_distance(points[i], points[j]) / 4.0;
			if (compare_double(sr, sR) > 0)
				continue;
			double r = sqrt(sr), dr = sqrt(sR - sr);
			point c;
			c.x = (points[i].x + points[j].x) / 2.0, c.y = (points[i].y + points[j].y) / 2.0;
			double dx = (points[i].y - points[j].y) * dr / (r * 2.0),
				dy = (points[i].x - points[j].x) * dr / (r * 2.0);
			int k;
			point mc; // modified center point, a bit above/below c
			mc.x = c.x - dx; mc.y = c.y + dy;
			for (k = 0; k < n; k++)
				if (compare_double(square_distance(mc, points[k]), sR) > 0)
					break;
			if (k == n)
				return true;
			mc.x = c.x + dx; mc.y = c.y - dy;
			for (k = 0; k < n; k++)
				if (square_distance(mc, points[k]) > sR)
					break;
			if (k == n)
				return true;
		}
	return false;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		double R;
		cin >> R;
		bool possible = true;
		if (n > 1)
			possible = pack_polygon(n, R);
		cout << ((possible) ? "The polygon can be packed in the circle.\n" : "There is no way of packing that polygon.\n");
	}
	return 0;
}

