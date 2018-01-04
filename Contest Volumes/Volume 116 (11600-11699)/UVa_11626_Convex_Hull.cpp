
/*
	UVa 11626 - Convex Hull

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11626_Convex_Hull.cpp
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int n_max = 100000;

struct point {
	long long x, y;
} points[n_max];

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
	return a.x < b.x || a.x == b.x && a.y < b.y;
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
	int t;
	cin >> t;
	while (t--) {
		int n, m = 0;
		cin >> n;
		while (n--) {
			char c;
			cin >> points[m].x >> points[m].y >> c;
			if (c == 'Y')
				m++;
		}
		// move the lowest leftmost point
		swap(points[0], *min_element(points, points + m, compare_position));
		// sort the second and later points in increasing angular order
		sort(points + 1, points + m, smaller_angle(points[0]));
		cout << m << endl;
		int i = 0, j = 1, k = 2;
		for ( ; k < m + 2; j = k++) {
			long long cp = cross_product(points[i], points[j % m], points[k % m]);
			if (cp < 0) // points[i], points[j], points[k] are clockwise
				;
			else {
				cout << points[i].x << ' ' << points[i].y << endl;
				if (j > i + 1) {
					for (int l = j; l > i + 1; l--)
						cout << points[l % m].x << ' ' << points[l % m].y << endl;
					swap(points[(i + 1) % m], points[j % m]);
				}
				i = j;
			}
		}
	}
	return 0;
}

