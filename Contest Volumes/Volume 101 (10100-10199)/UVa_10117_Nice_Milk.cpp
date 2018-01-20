
/*
	14.7.8 Nice Milk
	PC/UVa IDs: 111408/10117, Popularity: C, Success rate: low Level: 4

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10117_Nice_Milk.cpp
*/

/*
	Do a backtrack.
	For each iteration:
		Starting with the original points of the polygon, choose a pair of points k-times.
		For each iteration with a pair of points p1, p2:
			Get a directed dipped line that is on the left side of a vector from p1 to p2.
				The line has the same direction as the vector from p1 to p2.
			Get the points that the dipped line intersects with other line segments of the polygon, 
			and add them between the points in which the line intersects.
			Iterate all of the points of the polygon and remove the points that are on the right side of the line.
		Calculate the area of polygon in which some points are replaced by the above process, and 
		record the minimum area.
*/

#include <iostream>
#include <vector>
#include <cstdio>
#include <cfloat>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

#define EPSILON FLT_EPSILON /* DBL_EPSILON */

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return fabs(x - p.x) <= EPSILON && fabs(y - p.y) <= EPSILON;}
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
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

double cross_product(const point& o, const point& p, const point& q) // cross product of vector o -> p and o -> q
{
    return (p.x - o.x) * (q.y - o.y) - (p.y - o.y) * (q.x - o.x);
}

void get_dipped_points(int h, const point& p, const point& q, point& dp, point& dq)
{
	double x = p.y - q.y, y = q.x - p.x, t = h / euclidean_distance(p, q);
	dp.x = p.x + x * t; dp.y = p.y + y * t;
		// dp(p.x + h * cos(theta), p.y + h * sin(theta)), cos(theta) = x / distance(p, q), sin(theta) = y / distance(p, q)
	dq.x = q.x + x * t; dq.y = q.y + y * t;
}

point get_intersect_points(const point& p1, const point& p2, const point& q1, const point& q2)
{
	double hq1 = cross_product(p1, p2, q1), hq2 = cross_product(p2, p1, q2);
		// fabs(hq1) is the distance between q1 and the vector p1 -> p2,
		// fabs(hq2) is the distance between q1 and the vector p2 -> p1
	double hq = hq1 + hq2;
    return point((q1.x * hq2 + q2.x * hq1) / hq, (q1.y * hq2 + q2.y * hq1) / hq);
}

void dip_bread(int h, int i, int j, const vector<point>& points, const vector<point> dpoints, vector<point>& result)
{
	result.clear();
	point dp1, dp2;
	get_dipped_points(h, points[i], points[j], dp1, dp2);
	for (int i = 0; i < dpoints.size(); i++) {
		int j = (i + 1) % dpoints.size();
		double cpi = cross_product(dp1, dp2, dpoints[i]), cpj = cross_product(dp1, dp2, dpoints[j]);
		if (cpi < -EPSILON) // dpoints[i] is on the right side of vector dp1 -> dp2
			;
		else
			result.push_back(dpoints[i]);
		if (cpi > EPSILON && cpj < -EPSILON || cpi < -EPSILON && cpj > EPSILON)
			// the vector dp1 -> dp2 intersects with the vector dpoints[i] -> dpoints[j]
			result.push_back(get_intersect_points(dp1, dp2, dpoints[i], dpoints[j]));
	}
}

void cover_sides_of_bread_with_milk(int k, int l, int h, const vector<point>& points, vector<point> dpoints, double& min_area)
{
	if (k + l < points.size())
		cover_sides_of_bread_with_milk(k, l + 1, h, points, dpoints, min_area);
	dip_bread(h, l, (l + 1) % points.size(), points, dpoints, dpoints);
	if (k == 1) {
		double area = polygon_area(dpoints);
		if (area < min_area)
			min_area = area;
	}
	else
		cover_sides_of_bread_with_milk(k - 1, l + 1, h, points, dpoints, min_area);
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int n, k, h;
		cin >> n >> k >> h;
		if (!n && !k && !h)
			break;
		if (k > n)
			k = n;
		vector<point> points;
		for (int i = 0; i < n; i++) {
			point p;
			cin >> p.x >> p.y;
			points.push_back(p);
		}
		double area = polygon_area(points);
		double min_area = DBL_MAX;
		if (!h || !k)
			min_area = area;
		else {
			vector<point> dpoints(points);
			cover_sides_of_bread_with_milk(k, 0, h, points, dpoints, min_area);
		}
		printf("%.2f\n", area - min_area);
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

