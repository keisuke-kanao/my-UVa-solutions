
/*
	UVa 10577 - Bounding box

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10577_Bounding_box.cpp

	from 22 September 2001 - Waterloo local contest, Problem D
		(http://acm.student.cs.uwaterloo.ca/~acm00/010922/data/)
*/

#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

const double pi = 2.0 * acos(0.0);

struct point {
	double x_, y_;
	point() {}
	point(double x, double y) : x_(x), y_(y) {}
};

double square_distance(const point& p, const point& q)
{
	double dx = p.x_ - q.x_, dy = p.y_ - q.y_;
	return dx * dx + dy * dy;
}

point rotate(const point& o, const point& p, double angle) // rotate p around o by angle
{
	double dx = p.x_ - o.x_, dy = p.y_ - o.y_;
	return point(o.x_ + dx * cos(angle) - dy * sin(angle), o.y_ + dx * sin(angle) + dy * cos(angle));
}

int main()
{
	for (int p = 1; ; p++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		const int nr_points = 3;
		point A, B, C;
		scanf("%lf %lf", &A.x_, &A.y_);
		scanf("%lf %lf", &B.x_, &B.y_);
		scanf("%lf %lf", &C.x_, &C.y_);
		double as = square_distance(B, C), bs = square_distance(C, A), cs = square_distance(A, B);
		double ad = bs + cs - as, bd = cs + as - bs, cd = as + bs - cs;
		double ud = as * ad + bs * bd + cs * cd;
		point cc; // circumcenter
		cc.x_ = (as * ad * A.x_ + bs * bd * B.x_ + cs * cd * C.x_) / ud;
		cc.y_ = (as * ad * A.y_ + bs * bd * B.y_ + cs * cd * C.y_) / ud;
		double angle = pi * 2.0 / n;
		double x_min = A.x_, x_max = A.x_, y_min = A.y_, y_max = A.y_;
		for (int i = 1; i < n; i++) {
			point p = rotate(cc, A, angle * i);
			x_min = min(x_min, p.x_), x_max = max(x_max, p.x_);
			y_min = min(y_min, p.y_), y_max = max(y_max, p.y_);
		}
		printf("Polygon %d: %.3lf\n", p, (x_max - x_min) * (y_max - y_min));
	}
	return 0;
}

