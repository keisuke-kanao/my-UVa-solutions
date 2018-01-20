
/*
	14.7.5 Useless Tile Packers
	PC/UVa IDs: 111405/10065, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10065_Useless_Tile_Packers.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cfloat>
#include <cmath>
using namespace std;

#define EPSILON FLT_EPSILON /* DBL_EPSILON */

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return x == p.x && y == p.y;}
};

ostream& operator<<(ostream& os, const point& p)
{
	os << '(' << p.x << ", " << p.y << ')';
	return os;
}

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

double signed_triangle_area(const point& a, const point& b, const point& c)
{
	return (a.x * b.y - a.y * b.x + a.y * c.x - a.x * c.y + b.x * c.y - c.x * b.y) / 2.0;
}

bool collinear(const point& a, const point& b, const point& c)
{
	return fabs(signed_triangle_area(a, b, c)) <= EPSILON;
}

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool ccw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the left of a -> b (or, a - b - c are counterclockwise)
	return signed_triangle_area(a, b, c) > EPSILON;
}

bool cw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the right of a -> b (or, a - b - c are clockwise)
	return signed_triangle_area(a, b, c) < -EPSILON;
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

int convex_hull(vector<point>& points, vector<point>& hull)
{
	sort_and_remove_duplicates(points, left_lower); // sort the points in leftmost-lowest order
	vector<point>::iterator i = points.begin();
	i++;
	sort(i, points.end(), smaller_angle(points[0])); // sort the second and later points in increasing angular order
	hull.resize(points.size());
	hull[0] = points[0]; hull[1] = points[1];
	int j = 1;
	for (int i = 2; i < points.size(); ) {
		if (cw(hull[j - 1], hull[j], points[i]))
			j--; // remove hulll[j]
		else {
			if (!collinear(hull[j - 1], hull[j], points[i]))
				j++;
			hull[j] = points[i++];
		}
	}
	if (cw(hull[j - 1], hull[j], points[0]))
		;
	else
		j++;
	hull.resize(j);
	return hull.size();
}

void print_polygon(const vector<point>& points)
{
	for (vector<point>::const_iterator i = points.begin(); i != points.end(); i++)
		cout << *i << endl;
}

double polygon_area(const vector<point>& polygon)
{
	double area = 0.0;
	for (int i = 0; i < polygon.size(); i++) {
		int j = (i + 1) % polygon.size();
		area += polygon[i].x * polygon[j].y - polygon[j].x * polygon[i].y;
	}
	return area / 2.0;
}

int main(int /* argc */, char** /* argv */)
{
	// for each polygon, calculate its area and its convex hull area
	for (int nr_case = 0; ; nr_case++) {
		int nr_points;
		cin >> nr_points;
		if (!nr_points)
			break;
		vector<point> points;
		while (nr_points--) {
			point p;
			cin >> p.x >> p.y;
			points.push_back(p);
		}
		double parea = fabs(polygon_area(points));
		vector<point> hull;
		convex_hull(points, hull);
		double harea = fabs(polygon_area(hull));
		double wasted_space = (harea - parea) * 100.0 / harea;
#ifdef DEBUG
		printf("polygon = %.2f, convex hull = %.2f\n", parea, harea);
#endif
		printf("Tile #%d\nWasted Space = %.2f %%\n\n", nr_case + 1, wasted_space);
	}
	return 0;
}

