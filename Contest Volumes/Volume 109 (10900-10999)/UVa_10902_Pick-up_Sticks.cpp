
/*
	UVa 10902 - Pick-up Sticks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10902_Pick-up_Sticks.cpp
*/

#include <algorithm>
#include <vector>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

const double epsilon = numeric_limits<double>::epsilon();

struct point{
	double x_, y_;
};

struct segment{
	int n_;
	point s_, e_;
};

inline bool in_range(double l, double u, double d)
{
 	return d >= l && d <= u;
}

double direction(const point& p1, const point& p2, const point& p3)
{
	return (p1.x_ - p2.x_) * (p2.y_ - p3.y_) - (p2.x_ - p3.x_) * (p1.y_ - p2.y_);
}

bool on_segment(const point& p1, const point& p2, const point& p3)
{
	return in_range(min(p1.x_, p2.x_), max(p1.x_, p2.x_), p3.x_) && in_range(min(p1.y_, p2.y_), max(p1.y_, p2.y_), p3.y_);
}

bool segment_intersect(const point& p1, const point& p2, const point& p3, const point& p4)
{
	double d1 = direction(p3, p4, p1), d2 = direction(p3, p4, p2), d3 = direction(p1, p2, p3), d4 = direction(p1, p2, p4);
	if((d1 > epsilon && d2 < -epsilon || d1 < -epsilon && d2 > epsilon) && (d3 > epsilon && d4 < -epsilon || d3 < -epsilon && d4 > epsilon))
		return true;
	if (fabs(d1) < epsilon && on_segment(p3, p4, p1))
		return true;
	if (fabs(d2) < epsilon && on_segment(p3, p4, p2))
		return true;
	if (fabs(d3) < epsilon && on_segment(p1, p2, p3))
		return true;
	if (fabs(d4) < epsilon && on_segment(p1, p2, p4))
		return true;
	return false;
}

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		segment s;
		vector<segment> segments;
		s.n_ = 1;
		scanf("%lf %lf %lf %lf", &s.s_.x_, &s.s_.y_, &s.e_.x_, &s.e_.y_);
		segments.push_back(s);
		for (int i = 2; i <= n; i++) {
			s.n_ = i;
			scanf("%lf %lf %lf %lf", &s.s_.x_, &s.s_.y_, &s.e_.x_, &s.e_.y_);
			for (vector<segment>::iterator si = segments.begin(); si != segments.end(); ) {
				if (segment_intersect(si->s_, si->e_, s.s_, s.e_))
					segments.erase(si);
				else
					++si;
			}
			segments.push_back(s);
		}
		printf("Top sticks:");
		for (vector<segment>::const_iterator si = segments.begin(), se = segments.end(); si != se; ) {
			printf(" %d", si->n_);
			printf("%c", (++si != se) ? ',' : '.');
		}
		putchar('\n');
	}
	return 0;
}

