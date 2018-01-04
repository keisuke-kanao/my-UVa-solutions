
/*
	UVa 143 - Orchard Trees

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_143_Orchard_Trees.cpp
*/

#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdio>
using namespace std;

const double epsilon = numeric_limits<float>::epsilon();

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return x == p.x && y == p.y;}
};

bool left_lower(const point& p1, const point& p2)
{
	if (p1.x < p2.x)
		return true;
	else if (p1.x > p2.x)
		return false;
	else if (p1.y < p2.y)
		return true;
	else
		return false;
}

void sort_and_remove_duplicates(vector<point>& points, bool (*compare)(const point&, const point&) /* = left_lower */)
{
	sort(points.begin(), points.end(), compare); // sort the points in leftmost-lowest order
	for (vector<point>::iterator i = points.begin(); i != points.end(); ) { // remove the duplicate points
		vector<point>::iterator j = i;
		j++;
		if (j != points.end() && *i == *j)
			i = points.erase(i);
		else
			i++;
	}
}

double cross_product(const point& a, const point& b, const point& c)
{
	return a.x * b.y - a.y * b.x + a.y * c.x - a.x * c.y + b.x * c.y - c.x * b.y;
}

bool collinear(const point& a, const point& b, const point& c)
{
	return fabs(cross_product(a, b, c)) <= epsilon;
}

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool ccw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the left of a -> b (or, a - b - c are counterclockwise)
	return cross_product(a, b, c) > epsilon;
}

bool cw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the right of a -> b (or, a - b - c are clockwise)
	return cross_product(a, b, c) < -epsilon;
}

struct smaller_angle {
	const point& first;

	smaller_angle(const point& _first) : first(_first) {}
	bool operator() (const point& p1, const point& p2) const;
};

bool smaller_angle::operator() (const point& p1, const point& p2) const
{
	if (collinear(first, p1, p2))
		return euclidean_distance(first, p1) <= euclidean_distance(first, p2);
	else
		return ccw(first, p1, p2);
}

bool point_in_hull(const point& p, const vector<point>& hull)
{
	int n = hull.size();
	for (int i = 0; i < n; i++)
		if (cw(hull[i], hull[(i + 1) % n], p))
			return false;
	return true;
}

int main()
{
	while (true) {
		const int nr_points = 3;
		vector<point> points(nr_points);
		scanf("%lf %lf %lf %lf %lf %lf", &points[0].x, &points[0].y,
			&points[1].x, &points[1].y, &points[2].x, &points[2].y);
		if (points[0].x == 0.0 && points[0].y == 0.0 &&
			points[1].x == 0.0 && points[1].y == 0.0 && points[2].x == 0.0 && points[2].y == 0.0)
			break;
		sort_and_remove_duplicates(points, left_lower); // sort the points in leftmost-lowest order
		if (points.size() > 2)
			sort(points.begin() + 1, points.end(), smaller_angle(points[0])); // sort the second and later points in increasing angular order
		int x_min = static_cast<int>(ceil(points[0].x)), x_max = static_cast<int>(floor(points[0].x)),
			y_min = static_cast<int>(ceil(points[0].y)), y_max = static_cast<int>(floor(points[0].y));
		for (int i = 1; i < nr_points; i++) {
			x_min = min(x_min, static_cast<int>(ceil(points[i].x))), x_max = max(x_max, static_cast<int>(floor(points[i].x)));
			y_min = min(y_min, static_cast<int>(ceil(points[i].y))), y_max = max(y_max, static_cast<int>(floor(points[i].y)));
		}
		x_min = max(x_min, 1), x_max = min(x_max, 99), y_min = max(y_min, 1), y_max = min(y_max, 99);
		int n = 0;
		for (int x = x_min; x <= x_max; x++)
			for (int y = y_min; y <= y_max; y++)
				if (point_in_hull(point(x, y), points))
					n++;
		printf("%4d\n", n);
	}
	return 0;
}

