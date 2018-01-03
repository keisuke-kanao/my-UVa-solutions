
/*
	UVa 634 - Polygon

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_634_Polygon.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 1000;

struct point {
	double x, y;
};

point points[n_max];

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		double min_x = 0.0;
		for (int i = 0; i < n; i++) {
			cin >> points[i].x >> points[i].y;
			if (i)
				min_x = min(min_x, points[i].x);
			else
				min_x = points[i].x;
		}
		point p, q;
		cin >> q.x >> q.y;
		// p and q compose a horizontal line segment and p is outside of the polygon
		p.x = min_x - 1.0; p.y = q.y;
		int nr_crossed = 0;
		for (int i = 0; i < n; i++) {
			point& r = points[i], s = points[(i + 1) % n];
			if (r.x == s.x && // r, s compose a vertical line segment
				r.x > p.x && r.x < q.x) {
				double y_min = min(r.y, s.y), y_max = max(r.y, s.y);
				if (p.y > y_min && p.y < y_max) // line segment of r, s crosses the line segment of p, q
					nr_crossed++;
			}
		}
#ifdef DEBUG
		cout << "nr_crossed = " << nr_crossed << endl;
#endif
		cout << ((nr_crossed & 1) ? "T\n" : "F\n");
	}
	return 0;
}

