
/*
	UVa 11096 - Nails

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11096_Nails.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct point {
	long long x, y;
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = static_cast<double>(a.x - b.x), dy = static_cast<double>(a.y - b.y);
	return sqrt(dx * dx + dy * dy);
}

long long cross_product(const point& o, const point& a, const point& b)
{
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
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
	long long cp = cross_product(first, a, b);
	if(!cp)
		return euclidean_distance(first, a) < euclidean_distance(first, b);
	else
		return cp > 0;
}

int main()
{
	int N;
	cin >> N;
	while (N--) {
		double r;
		int n;
		cin >> r >> n;
		vector<point> points(n);
		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		double rr = 0.0;
		if (n == 2)
			rr = euclidean_distance(points[0], points[1]) * 2;
		else if (n > 2) {
			// apply Graham's scan to compute the convex hull of points

			// move the lowest leftmost point
			swap(points[0], *min_element(points.begin(), points.end(), compare_position));
			// sort the second and later points in increasing angular order
			sort(points.begin() + 1, points.end(), smaller_angle(points[0]));
			points.push_back(points[0]);
			vector<point> hull(n + 1);
			int hn = 2;
			hull[0] = points[0]; hull[1] = points[1];
			for(int i = 2; i <= n; i++) {
				while (hn >= 2 && cross_product(hull[hn - 2], hull[hn - 1], points[i]) < 0)
					hn--;
				hull[hn++] = points[i];
			}
			for (int i = 0; i < hn - 1; i++)
				rr += euclidean_distance(hull[i], hull[i + 1]);
		}
		cout << fixed << setprecision(5) << ((rr > r) ? rr : static_cast<double>(r)) << endl;
	}
	return 0;
}

