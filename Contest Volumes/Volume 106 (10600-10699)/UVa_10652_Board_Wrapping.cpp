
/*
	UVa 10652 - Board Wrapping

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10652_Board_Wrapping.cpp
*/

#include <algorithm>
#include <vector>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

const double epsilon = numeric_limits<float>::epsilon();
const double pi = 2.0 * acos(0.0);

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return x == p.x && y == p.y;}
};

/*
let (x0, y0) be the lower left corner of the rectangle, then:
center point: (x0 + w / 2, y0 + h / 2)
rotate the center point around (x0, y0), by (-a):
(
	x: cos(-a) * (x0 + w / 2 - x0) - sin(-a) * (y0 + h / 2 - y0) + x0 = cos(a) * w / 2 + sin(a) * h / 2 + x0,
	y: sin(-a) * (x0 + w / 2 - x0) + cos(-a) * (y0 + h / 2 - y0) + y0 = -sin(a) * w / 2 + cos(a) * h / 2 + y0
)

x0 = x - (cos(a) * w + sin(a) * h) / 2;
y0 = y + (sin(a) * w - cos(a) * h) / 2;

rotate the other 3 points:
	(x0, y0 + h):
		cos(-a) * (x0 - x0) - sin(-a) * (y0 + h - y0) + x0 = sin(a) * h + x0
		sin(-a) * (x0 - x0) + cos(-a) * (y0 + h - y0) + y0 = cos(a) * h + y0

	(x0 + w, y0):
		cos(-a) * (x0 + w - x0) - sin(-a) * (y0 - y0) + x0 = cos(a) * w + x0
		sin(-a) * (x0 + w - x0) + cos(-a) * (y0 - y0) + y0 = -sin(a) * w + y0

	(x0 + w, y0 + h):
		cos(-a) * (x0 + w - x0) - sin(-a) * (y0 + h - y0) + x0 = cos(a) * w + sin(a) * h + x0
		sin(-a) * (x0 + w - x0) + cos(-a) * (y0 + h - y0) + y0 = -sin(a) * w + cos(a) * h + y0

*/

void add_rectangle_points(double x, double y, double w, double h, double a, vector<point>& points)
{
	// lower left corner
	double x0 = x - (cos(a) * w + sin(a) * h) / 2, y0 = y + (sin(a) * w - cos(a) * h) / 2;
	points.push_back(point(x0, y0));
	points.push_back(point(sin(a) * h + x0, cos(a) * h + y0));
	points.push_back(point(cos(a) * w + x0, -sin(a) * w + y0));
	points.push_back(point(cos(a) * w + sin(a) * h + x0, -sin(a) * w + cos(a) * h + y0));
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
	return hull.size();
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

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		int n;
		scanf("%d", &n);
		vector<point> points;
		double ra = 0.0;
		for (int i = 0; i < n; i++) {
			double x, y, w, h, phi;
			scanf("%lf %lf %lf %lf %lf", &x, &y, &w, &h, &phi);
			add_rectangle_points(x, y, w, h, phi * pi / 180.0, points);
			ra += w * h;
		}
#ifdef DEBUG
		for (size_t i = 0; i < points.size(); i++)
			printf("%lf %lf\n", points[i].x, points[i].y);
#endif
		vector<point> hull(n * 4);
		convex_hull(points, hull);
#ifdef DEBUG
		for (size_t i = 0; i < hull.size(); i++)
			printf("%lf %lf\n", hull[i].x, hull[i].y);
#endif
		double area = polygon_area(hull);
		printf("%.1lf %%\n", ra * 100.0 / area);
	}
	return 0;
}

