
/*
	UVa 361 - Cops and Robbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_361_Cops_and_Robbers.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const int c_max = 200, r_max = 200;

struct point {
	int x, y;
} cops[c_max + 1], robbers[r_max + 1], cops_hull[c_max + 1], robbers_hull[r_max + 1];

double euclidean_distance(const point& a, const point& b)
{
	double dx = static_cast<double>(a.x - b.x), dy = static_cast<double>(a.y - b.y);
	return sqrt(dx * dx + dy * dy);
}

bool left_lower(const point& a, const point& b)
{
	if (a.x < b.x)
		return true;
	else if (a.x > b.x)
		return false;
	else if (a.y < b.y)
		return true;
	else
		return false;
}

bool compare_position(const point& a, const point& b)
{
	return a.x == b.x && a.y == b.y;
}

int cross_product(const point& o, const point& a, const point& b)
{
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

struct smaller_angle {
	const point& first;

	smaller_angle(const point& _first) : first(_first) {}
	bool operator() (const point& a, const point& b);
};

bool smaller_angle::operator() (const point& a, const point& b)
{
	int cp = cross_product(first, a, b);
	if(!cp)
		return euclidean_distance(first, a) < euclidean_distance(first, b);
	else
		return cp > 0;
}

int convex_hull(int n, point points[], point hull[])
{
	// apply Graham's scan to compute the convex hull of points
	// sort the points and remove the duplicates
	sort(points, points + n, left_lower);
	n = unique(points, points + n, compare_position) - points;
	// sort the second and later points in increasing angular order
	sort(points + 1, points + n, smaller_angle(points[0]));
	int hn = 0;
	for (int i = 0; i < n; i++) {
		while (hn >= 2 && cross_product(hull[hn - 2], hull[hn - 1], points[i]) <= 0)
			hn--;
		hull[hn++] = points[i];
	}
#ifdef DEBUG
	for (int i = 0; i < hn; i++)
		printf("(%d, %d)%c", hull[i].x, hull[i].y, ((i < hn - 1) ? ' ' : '\n'));
#endif
	for (int i = n - 1, t = hn + 1; i >= 0; i--) {
		while (hn >= t && cross_product(hull[hn - 2], hull[hn -  1], points[i]) <= 0)
			hn--;
		hull[hn++] = points[i];
	}
#ifdef DEBUG
	for (int i = 0; i < hn; i++)
		printf("(%d, %d)%c", hull[i].x, hull[i].y, ((i < hn - 1) ? ' ' : '\n'));
#endif
	return hn;
}

bool point_in_hull(const point& p, int n, const point hull[])
{
	int hn = n - 1;
	if (hn == 1)
		return compare_position(p, hull[0]);
	else if (hn == 2)
		return !cross_product(hull[0], hull[1], p) &&
			p.x >= min(hull[0].x, hull[1].x) && p.x <= max(hull[0].x, hull[1].x) &&
			p.y >= min(hull[0].y, hull[1].y) && p.y <= max(hull[0].y, hull[1].y);
	else {
		for (int i = 0; i < hn; i++)
			if (cross_product(hull[i], hull[i + 1], p) < 0)
				return false;
		return true;
	}
}

int main()
{
	for (int ds = 1; ; ds++) {
		int c, r, o, hc, hr;
		scanf("%d %d %d", &c, &r, &o);
		if (!c && !r && !o)
			break;
		for (int i = 0; i < c; i++)
			scanf("%d %d", &cops[i].x, &cops[i].y);
		for (int i = 0; i < r; i++)
			scanf("%d %d", &robbers[i].x, &robbers[i].y);
		if (c > 2)
			hc = convex_hull(c, cops, cops_hull);
		if (r > 2)
			hr = convex_hull(r, robbers, robbers_hull);
		printf("Data set %d:\n", ds);
		while (o--) {
			point p;
			scanf("%d %d", &p.x, &p.y);
			printf("     Citizen at (%d,%d) is ", p.x, p.y);
			if (c > 2 && point_in_hull(p, hc, cops_hull))
				puts("safe.");
			else if (r > 2 && point_in_hull(p, hr, robbers_hull))
				puts("robbed.");
			else
				puts("neither.");
		}
		putchar('\n');
	}
	return 0;
}

