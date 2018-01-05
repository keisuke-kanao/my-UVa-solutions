
/*
	UVa 10173 - Smallest Bounding Rectangle

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10173_Smallest_Bounding_Rectangle.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

const double epsilon = numeric_limits<float>::epsilon();

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
	return fabs(signed_triangle_area(a, b, c)) <= epsilon;
}

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool ccw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the left of a -> b (or, a - b - c are counterclockwise)
	return signed_triangle_area(a, b, c) > epsilon;
}

bool cw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the right of a -> b (or, a - b - c are clockwise)
	return signed_triangle_area(a, b, c) < -epsilon;
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
#ifdef DEBUG
	for (int i = 0; i < hull.size(); i++) {
		if (i)
			cout << ' ';
		cout << hull[i];
	}
	cout << endl;
#endif
	return hull.size();
}

bool point_in_hull(point& p, const vector<point>& hull)
{
	int n = hull.size();
	for (int i = 0; i < n; i++)
		if (cw(hull[i], hull[(i + 1) % n], p))
			return false;
	return true;
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

point rotate_point(const point& o, const point& p, double angle) // rotate p by angle around o
{
	if (fabs(angle) < epsilon)
		angle = 0.0;
	double x = p.x - o.x, y = p.y - o.y;
	return point(o.x + x * cos(angle) - y * sin(angle), o.y + x * sin(angle) + y * cos(angle));
}

double min_bounding_rectangle_area(const vector<point>& hull)
{
/*
	for each edge of the convex hull:
	  compute the edge orientation.
	  rotate the convex hull using this orientation.
	  calculate the bounding rectangle area with min/max of x/y of the rotated convex hull.
*/
	int n = hull.size();
	double min_area = numeric_limits<double>::max();
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		double angle = atan2(hull[j].y - hull[i].y, hull[j].x - hull[i].x);
		double min_x = hull[i].x, min_y = hull[i].y, max_x = hull[i].x, max_y = hull[i].y;
		for ( ; j != i; j = (j + 1) % n) {
			point p = rotate_point(hull[i], hull[j], -angle);
			min_x = min(min_x, p.x); min_y = min(min_y, p.y);
			max_x = max(max_x, p.x); max_y = max(max_y, p.y);
		}
#ifdef DEBUG
		cout << angle << ' ' << point(min_x, min_y) << ' ' << point(max_x, max_y) << endl;
#endif
		min_area = min(min_area, (max_x - min_x) * (max_y - min_y));
	}
	return min_area;
}

int main()
{
	const int n_max = 1000;
	vector<point> points(n_max);
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		points.resize(n);
		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		double area = 0.0;
		if (n > 2) {
			vector<point> hull(n);
			convex_hull(points, hull);
			area = min_bounding_rectangle_area(hull);
		}
		cout << fixed << setprecision(4) << area << endl;
	}
	return 0;
}

/*
Sample Input

3
-3.000 5.000
7.000 9.000
17.000 5.000
4
10.000 10.000
10.000 20.000
20.000 20.000
20.000 10.000
0 

Sample Output

80.0000
100.0000

*/

