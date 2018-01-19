
/*
	7.6.8 Repackaging
	PC/UVa IDs: 110708/10089, Popularity: C, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10089_Repackaging.cpp
*/

/*
Convert each package (s1, s2, s3) to a vector (s1 - s3, s2 - s3).
Find the convex hull for the vectors.
See if (0, 0) is within the convex hull.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
	long long x, y;

	point() : x(0), y(0) {}
	point(long long _x, long long _y) : x(_x), y(_y) {}
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

long long signed_triangle_area(const point& a, const point& b, const point& c)
{
	return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) / 2;
}

bool collinear(const point& a, const point& b, const point& c)
{
	return !((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

long long square_distance(const point& a, const point& b)
{
	long long dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

bool ccw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the left of a -> b (or, a - b - c are counterclockwise)
	return  (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0;
}

bool cw(const point& a, const point& b, const point& c)
{
	// see if the point c is to the right of a -> b (or, a - b - c are clockwise)
	return  (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) < 0;
}

struct smaller_angle {
	const point& first;

	smaller_angle(const point& _first) : first(_first) {}
	bool operator() (const point& p1, const point& p2);
};

bool smaller_angle::operator() (const point& p1, const point& p2)
{
	if (collinear(first, p1, p2))
		return square_distance(first, p1) <= square_distance(first, p2);
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

bool original_point_in_hull(const vector<point>& hull)
{
	int nr_ccw = 0;
	for (int i = 0; i < hull.size(); i++) {
		int j = (i + 1) % hull.size();
		long long cp = hull[i].x * hull[j].y - hull[i].y * hull[j].x; // cross product of hull[i], hull[j], and the original point
		if (cp < 0) // the original point is to the right of hull[i] -> hull[j]
			return false;
		else if (cp > 0) // the original point is to the left of hull[i] -> hull[j]
			nr_ccw++;
		else { // hull[i], hull[j], and the original point are collinear
			long long dp = hull[i].x * (hull[i].x - hull[j].x) + hull[i].y * (hull[i].y - hull[j].y);
				// dot product of hull[i], hull[j], and the original point
			if (dp > 0 && dp <= square_distance(hull[i], hull[j]))
				return true; // the original point is on the line segment of hull[i], hull[j]
		}
	}
	return nr_ccw == hull.size();
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int nr_packages;
		cin >> nr_packages;
		if (!nr_packages)
			break;
		vector<point> points(nr_packages);
		for (int i = 0; i < nr_packages; i++) {
			long long s1, s2, s3;
			cin >> s1 >> s2 >> s3;
			points[i].x = s2 - s1; points[i].y = s3 - s1;
		}
		vector<point> hull;
		convex_hull(points, hull);
		cout << ((original_point_in_hull(hull)) ? "Yes\n" : "No\n");
	}
	return 0;
}

