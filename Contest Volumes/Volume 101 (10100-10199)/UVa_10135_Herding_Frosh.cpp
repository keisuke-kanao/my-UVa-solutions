
/*
	14.7.1 Herding Frosh
	PC/UVa IDs: 111401/10135, Popularity: C, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10135_Herding_Frosh.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cfloat>
#include <cmath>
using namespace std;

#define EPSILON FLT_EPSILON /* DBL_EPSILON */

const double pi = 2.0 * acos(0.0); // 3.14159265358979323846

struct point {
	double x, y;

	point() : x(0.0), y(0.0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return x == p.x && y == p.y;}
};

#ifdef DEBUG
ostream& operator<<(ostream& os, const point& p)
{
	os << '(' << p.x << ", " << p.y << ')';
	return os;
}
#endif

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

#ifdef DEBUG
void print_polygon(const vector<point>& points)
{
	for (vector<point>::const_iterator i = points.begin(); i != points.end(); i++)
		cout << *i << endl;
}
#endif

struct smaller_polar_angle {
	point p;
	double angle;

	smaller_polar_angle(const point& _p) : p(_p), angle(atan2(p.y, p.x)) {}
	bool operator() (const point& p1, const point& p2) const;
};

bool smaller_polar_angle::operator() (const point& p1, const point& p2) const
{
	double a1 = atan2(p1.y, p1.x) - angle, a2 = atan2(p2.y, p2.x) - angle;

	if (fabs(a1 - a2) <= EPSILON)
		return euclidean_distance(p, p1) < euclidean_distance(p, p2);

	if (a1 < 0)
		a1 += pi * 2.0;
	if (a2 < 0)
		a2 += pi * 2.0;
	return a1 < a2;
}

int convex_hull_ex(vector<point>& points, vector<point>& hull)
{
	point original_point;
	hull.resize(points.size());
	hull[0] = points[0]; hull[1] = points[1];
	int j = 1;
	for (int i = 2; i < points.size(); ) {
		if (!j)
			hull[++j] = points[i++];
		else if (cw(hull[j - 1], hull[j], points[i])) {
			if (hull[j] == original_point)
				hull[++j] = points[i++];
			else
				j--; // remove hulll[j]
		}
		else {
/*
			if (hull[j] == original_point || !collinear(hull[j - 1], hull[j], points[i]))
*/
				j++;
			hull[j] = points[i++];
		}
	}
	for ( ; j; j--) {
		if (hull[j] == original_point)
			break;
		else if (cw(hull[j - 1], hull[j], points[0]))
			;
		else
			break;
	}
	j++;
	hull.resize(j);
	return hull.size();
}

double polygon_perimeter(const vector<point>& polygon)
{
	double perimeter = 0.0;
	for (int i = 0; i < polygon.size(); i++) {
		int j = (i + 1) % polygon.size();
		perimeter += euclidean_distance(polygon[i], polygon[j]);
	}
	return perimeter;
}

int main(int /* argc */, char** /* argv */)
{
	int nr_cases;
	cin >> nr_cases;
	for (int c = 0; c < nr_cases; c++) {
		int nr_frosh;
		cin >> nr_frosh;
		point original_point;
		vector<point> frosh(nr_frosh + 1);
		frosh[0] = original_point;
		for (int i = 1; i <= nr_frosh; i++)
			cin >> frosh[i].y >> frosh[i].x;

		if (nr_frosh < 2) { // special cases
			double perimeter = (nr_frosh) ?
				2.0 /* one extra meter at each end */ + euclidean_distance(frosh[0], frosh[1]) * 2.0 : 2.0;
			printf("%.2f\n", perimeter);
			if (c < nr_cases - 1)
				cout << endl; // print a blank line between the two consecutive cases
			continue;
		}

		vector<point> hull;
		convex_hull(frosh, hull);
			// if a frosh is at the original point, the convex_hull function removes the duplicate points.
#ifdef DEBUG
		cout << endl; print_polygon(hull);
#endif
		double min_perimeter = DBL_MAX;
		if (find(hull.begin(), hull.end(), original_point) != hull.end())
			// the original point is one of the vertices of the convex hull
			min_perimeter = polygon_perimeter(hull);
		else {
			frosh.erase(find(frosh.begin(), frosh.end(), original_point));
			nr_frosh = frosh.size();
			vector<point>::iterator i = frosh.begin();
			i++;
			// sort the 2nd and and later points by their polar angles, being the angle of the 1st point as the reference one
			sort(i, frosh.end(), smaller_polar_angle(frosh[0]));
#ifdef DEBUG
			cout << endl; print_polygon(frosh);
#endif
			for (int j = 0; j < nr_frosh; j++) {
				i = frosh.insert(i, original_point);
				// calculate the convex hull except for the original point and its neigbors
				convex_hull_ex(frosh, hull);
				double perimeter = polygon_perimeter(hull);
#ifdef DEBUG
				cout << endl; print_polygon(hull);
				cout << perimeter << endl;
#endif
				min_perimeter = min(min_perimeter, perimeter);
				i = frosh.erase(i);
				if (i != frosh.end())
					i++;
			}
		}
		printf("%.2f\n", 2.0 /* one extra meter at each end */ + min_perimeter);
		if (c < nr_cases - 1)
			cout << endl; // print a blank line between the two consecutive cases
	}
	return 0;
}

