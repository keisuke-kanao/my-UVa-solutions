
/*
	UVa 10406 - Cutting tabletops

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10406_Cutting_tabletops.cpp
*/

#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

const double epsilon = numeric_limits<float>::epsilon();

struct point {
	double x_, y_;

	point() {}
	point(double x, double y) : x_(x), y_(y) {}
	point(const point &p) : x_(p.x_), y_(p.y_) {}
	bool operator==(const point& p) const {return fabs(x_ - p.x_) <= epsilon && fabs(y_ - p.y_) <= epsilon;}
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x_ - b.x_, dy = a.y_ - b.y_;
	return sqrt(dx * dx + dy * dy);
}

/*
bool left_lower(const point& a, const point& b)
{
	if (a.x_ < b.x_)
		return true;
	else if (a.x_ > b.x_)
		return false;
	else if (a.y_ < b.y_)
		return true;
	else
		return false;
}
*/

double cross_product(const point& o, const point& a, const point& b)
{
	return (a.x_ - o.x_) * (b.y_ - o.y_) - (b.x_ - o.x_) * (a.y_ - o.y_);
}

/*
struct smaller_angle {
	const point& first;

	smaller_angle(const point& _first) : first(_first) {}
	bool operator() (const point& a, const point& b);
};

bool smaller_angle::operator() (const point& a, const point& b)
{
	double cp = cross_product(first, a, b);
	if(fabs(cp) <= epsilon) // collinear
		return euclidean_distance(first, a) < euclidean_distance(first, b);
	else
		return cp > epsilon; // counterclockwise
}

int convex_hull(int n, const vector<point>& points, vector<point>& hull)
{
	// apply Graham's scan to compute the convex hull of points
	int hn = 0;
	for (int i = 0; i < n; i++) {
		while (hn >= 2) {
			double cp = cross_product(hull[hn - 2], hull[hn - 1], points[i]);
			if (cp < -epsilon || fabs(cp) <= epsilon) // clockwise or collinear
				hn--;
		}
		hull[hn++] = points[i];
	}
#ifdef DEBUG
	for (int i = 0; i < hn; i++)
		printf("(%d, %d)%c", hull[i].x_, hull[i].y_, ((i < hn - 1) ? ' ' : '\n'));
#endif
	for (int i = n - 1, t = hn + 1; i >= 0; i--) {
		while (hn >= t) {
			double cp = cross_product(hull[hn - 2], hull[hn -  1], points[i]);
			if (cp < -epsilon || fabs(cp) <= epsilon) // clockwise or collinear
				hn--;
		}
		hull[hn++] = points[i];
	}
#ifdef DEBUG
	for (int i = 0; i < hn; i++)
		printf("(%d, %d)%c", hull[i].x_, hull[i].y_, ((i < hn - 1) ? ' ' : '\n'));
#endif
	return hn;
}
*/

void get_cut_points(double d, const point& p, const point& q, point& cp, point& cq)
{
	double x = p.y_ - q.y_, y = q.x_ - p.x_, t = d / euclidean_distance(p, q);
	cp.x_ = p.x_ + x * t; cp.y_ = p.y_ + y * t;
		// cp(p.x_ + d * cos(theta), p.y_ + d * sin(theta)), 
		// cos(theta) = x / distance(p, q), sin(theta) = y / distance(p, q)
	cq.x_ = q.x_ + x * t; cq.y_ = q.y_ + y * t;
}

point get_intersect_points(const point& p1, const point& p2, const point& q1, const point& q2)
{
	double hq1 = cross_product(p1, p2, q1), hq2 = cross_product(p2, p1, q2);
		// fabs(hq1) is the distance between q1 and the vector p1 -> p2,
		// fabs(hq2) is the distance between q2 and the vector p2 -> p1
	double hq = hq1 + hq2;
    return point((q1.x_ * hq2 + q2.x_ * hq1) / hq, (q1.y_ * hq2 + q2.y_ * hq1) / hq);
}

double polygon_area(int n, const vector<point>& polygon)
{
	double area = 0.0;
	for (int i = 0; i < n; i++)
		area += polygon[i].x_ * polygon[(i + 1) % n].y_ - polygon[(i + 1) % n].x_ * polygon[i].y_;
	return area / 2.0;
}

#ifdef DEBUG
void print_polygon(int n, const vector<point>& polygon)
{
	for (int i = 0; i < n; i++)
		printf("(%.3lf, %.3lf)%c", polygon[i].x_, polygon[i].y_, ((i < n - 1) ? ' ' : '\n'));
}
#endif

int main()
{
	while (true) {
		double d;
		int n;
		scanf("%lf %d", &d, &n);
		if (d == 0.0 && n == 0)
			break;
		vector<point> points(n);
		for (int i = n - 1; i >= 0; i--)
			scanf("%lf %lf", &points[i].x_, &points[i].y_);
/*
		// sort the points and remove the duplicates
		sort(points.begin(), points.end(), left_lower);
		points.resize(distance(points.begin(), unique(points.begin(), points.end())));
		n = static_cast<int>(points.size());
		// sort the second and later points in increasing angular order
		sort(points.begin(), points.end(), smaller_angle(points[0]));
*/
		vector<point> cpoints(n * 2);
		for (int i = 0; i < n; i++)
			get_cut_points(d, points[i], points[(i + 1) % n], cpoints[i * 2], cpoints[i * 2 + 1]);
#ifdef DEBUG
		print_polygon(n * 2, cpoints);
#endif
		for (int i = 0; i < n; i++)
			points[i] = get_intersect_points(cpoints[i * 2], cpoints[i * 2 + 1], cpoints[(i * 2 + 2) % (n * 2)], cpoints[(i * 2 + 3) % (n * 2)]);
#ifdef DEBUG
		print_polygon(n, points);
#endif
		printf("%.3lf\n", polygon_area(n, points));
	}
	return 0;
}

