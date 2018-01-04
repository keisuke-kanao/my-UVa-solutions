
/*
	UVa 218 - Moth Eradication

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_218_Moth_Eradication.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

#define EPSILON numeric_limits<float>::epsilon()

struct point {
	double x, y;
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

double cross_product(const point& o, const point& a, const point& b)
{
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

bool collinear(const point& o, const point& a, const point& b)
{
	return fabs(cross_product(o, a, b)) <= EPSILON;
}

bool ccw(const point& o, const point& a, const point& b)
{
	// see if the point b is to the left of o -> a (or, o - a - b are counterclockwise)
	return cross_product(o, a, b) > EPSILON;
}

bool cw(const point& o, const point& a, const point& b)
{
	// see if the point b is to the right of o -> a (or, o - a - b are clockwise)
	return cross_product(o, a, b) < -EPSILON;
}

bool compare_position(const point& a, const point& b)
{
	return a.y < b.y || a.y == b.y && a.x < b.x;
}

struct smaller_angle {
	const point& first;

	smaller_angle(const point& _first) : first(_first) {}
	bool operator() (const point& p1, const point& p2);
};

bool smaller_angle::operator() (const point& a, const point& b)
{
	double cp = cross_product(first, a, b);
	if(fabs(cp) <= EPSILON)
		return euclidean_distance(first, a) < euclidean_distance(first, b);
	else
		return cp > EPSILON;
}

double polygon_perimeter(const vector<point>& points)
{
	double perimeter = 0.0;
	for (size_t i = 0, s = points.size(); i < s; i++) {
		size_t j = (i + 1) % s;
		perimeter += euclidean_distance(points[i], points[j]);
	}
	return perimeter;
}

int main()
{
	for (int region_nr = 1; ; region_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<point> points(n);
		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		// move the lowest leftmost point
		swap(points[0], *min_element(points.begin(), points.end(), compare_position));
		vector<point>::iterator pi = points.begin();
		pi++;
		sort(pi, points.end(), smaller_angle(points[0])); // sort the second and later points in increasing angular order
		vector<point> hull(n);
		int hn = 2;
		hull[0] = points[0]; hull[1] = points[1];
		for(int i = 2; i < n; i++) {
			while (hn >= 2 && !ccw(hull[hn - 2], hull[hn - 1], points[i]))
				hn--;
			hull[hn++] = points[i];
		}
		hull.resize(hn);
		double perimeter = polygon_perimeter(hull);
		if (region_nr > 1)
			cout << endl;
		cout << "Region #" << region_nr << ":\n";
		cout << '(' << fixed << setprecision(1) << hull[0].x << ',' << setprecision(1) << hull[0].y << ')';
		for (int i = static_cast<int>(hull.size()) - 1; i >= 0; i--)
			cout << "-(" << setprecision(1) << hull[i].x << ',' << setprecision(1) << hull[i].y << ')';
		cout << "\nPerimeter length = " << setprecision(2) <<  perimeter << endl;
	}
	return 0;
}

