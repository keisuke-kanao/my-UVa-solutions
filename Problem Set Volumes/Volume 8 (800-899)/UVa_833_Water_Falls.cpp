
/*
	UVa 833 - Water Falls

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_833_Water_Falls.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <cmath>
using namespace std;

const double epsilon = numeric_limits<float>::epsilon();

/*
The slope of the line through points A(xa, ya) and B(xb, yb), when xa != xb, is given by m = (yb - ya) / (xb - xa) and 
the equation of this line can be written y = m(x - xa) + ya.
For the point P(xp, yp), if the P is above the line, then:
	yp >= m(x0 - xa) + ya = ((yb - ya) / (xb - xa)) * (xp - xa) + ya, or
	(yp - ya) * (xb - xa) >= (yb - ya) * (xp - xa)
*/

struct point {
	double x, y;
};

struct line_segment {
	point p1, p2;

	bool operator<(const line_segment& ls) const {return p1.x < ls.p1.x;}
};

int compare_double(double d1, double d2)
{
	double d = d1 - d2;
	if (fabs(d) < epsilon)
		return 0;
	else if (d > 0.0)
		return 1;
	else
		return -1;
}

void water_fall(int n, const vector<line_segment>& line_segments, point& p)
{
	line_segment ls;
	ls.p1.x = p.x;
	int i = distance(line_segments.begin(), lower_bound(line_segments.begin(), line_segments.end(), ls)) - 1;
	if (i == -1) {
		p.y = 0.0;
		return;
	}
	int j;
	double y_max = 0.0;
	for ( ; i >= 0; i--) { // find a line segment that is immediately below p
		const line_segment& rls = line_segments[i];
		if (p.x < rls.p2.x) {
			double y = (rls.p2.y - rls.p1.y) * (p.x - rls.p1.x) / (rls.p2.x - rls.p1.x) + rls.p1.y;
			if (compare_double(y, p.y) <= 0 && compare_double(y, y_max) > 0) {
				j = i;
				y_max = y;
			}
		}
	}
	if (compare_double(y_max, 0.0) > 0) {
		const line_segment& rls = line_segments[j];
		if (rls.p1.y < rls.p2.y) {
			p.x =rls.p1.x; p.y = rls.p1.y;
		}
		else {
			p.x = rls.p2.x; p.y = rls.p2.y;
		}
	}
	else {
		p.y = 0.0;
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int np;
		cin >> np;
		int n = 0;
		vector<line_segment> line_segments(np);
		while (np--) {
			cin >> line_segments[n].p1.x >> line_segments[n].p1.y >> line_segments[n].p2.x >> line_segments[n].p2.y;
			if (line_segments[n].p1.x != line_segments[n].p2.x) { // not a vertical line
				if (line_segments[n].p1.x > line_segments[n].p2.x) {
					swap(line_segments[n].p1.x, line_segments[n].p2.x);
					swap(line_segments[n].p1.y, line_segments[n].p2.y);
				}
				n++;
			}
		}
		line_segments.resize(n);
		sort(line_segments.begin(), line_segments.end());
		int ns;
		cin >> ns;
		while (ns--) {
			point p;
			cin >> p.x >> p.y;
			do {
				water_fall(n, line_segments, p);
#ifdef DEBUG
				cout << p.x << ' ' << p.y << endl;
#endif
			}
			while (p.y != 0.0);
			cout << fixed << setprecision(0) << p.x << endl;
		}
		if (t)
			cout << endl;
	}
	return 0;
}

/*
Sample Input 

1

4
14 7 3 4
11 13 16 11
1 10 6 7
2 1 4 3
3
10 4
14 14
2 13

Sample Output 

10
16
2

*/

