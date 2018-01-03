
/*
	UVa 681 - Convex Hull Finding

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_681_Convex_Hull_Finding.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct point {
	int x, y;
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = static_cast<double>(a.x - b.x), dy = static_cast<double>(a.y - b.y);
	return sqrt(dx * dx + dy * dy);
}

int cross_product(const point& o, const point& a, const point& b)
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
	int cp = cross_product(first, a, b);
	if(!cp)
		return euclidean_distance(first, a) < euclidean_distance(first, b);
	else
		return cp > 0;
}

int main()
{
	int k;
	cin >> k;
	cout << k << endl;
	while (k--) {
		int n;
		cin >> n;
		vector<point> points(n);
		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		int delimiter = 0;
		if (k)
			cin >> delimiter;
		// move the lowest leftmost point
		swap(points[0], *min_element(points.begin(), points.end(), compare_position));
		vector<point>::iterator pi = points.begin();
		pi++;
		sort(pi, points.end(), smaller_angle(points[0])); // sort the second and later points in increasing angular order
		points.push_back(points[0]);
		vector<point> hull(n + 1);
		int hn = 2;
		hull[0] = points[0]; hull[1] = points[1];
		for(int i = 2; i <= n; i++) {
			while (hn >= 2 && cross_product(hull[hn - 2], hull[hn - 1], points[i]) <= 0)
				hn--;
			hull[hn++] = points[i];
		}
		cout << hn << endl;
		for (int i = 0; i < hn; i++)
			cout << hull[i].x << ' ' << hull[i].y << endl;
		if (delimiter)
			cout << delimiter << endl;
	}
	return 0;
}

