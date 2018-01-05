
/*
	UVa 11178 - Morley's Theorem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11178_Morleys_Theorem.cpp
*/

#include <cstdio>
#include <cmath>

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

point pA, pB, pC, pD, pE, pF;
double as, bs, cs, a, b, c, A, B, C;

point trilinear_to_cartesian(double x, double y, double z)
{
	double d = a * x + b * y + c * z;
	return point(a * x / d * pA.x_ + b * y / d * pB.x_ + c * z / d * pC.x_,
		a * x / d * pA.y_ + b * y / d * pB.y_ + c * z / d * pC.y_);
}
 
int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		scanf("%lf %lf %lf %lf %lf %lf", &pA.x_, &pA.y_, &pB.x_, &pB.y_, &pC.x_, &pC.y_);
		as = square_distance(pB, pC), bs = square_distance(pC, pA), cs = square_distance(pA, pB);
		a = sqrt(as), b = sqrt(bs), c = sqrt(cs);
		A = acos((bs + cs - as) / (2.0 * b * c)), B = acos((cs + as - bs) / (2.0 * c * a)),
			C = acos((as + bs - cs) / (2.0 * a * b));
		pD = trilinear_to_cartesian(1.0, 2.0 * cos(C / 3.0), 2.0 * cos(B / 3.0)),
			pE = trilinear_to_cartesian(2.0 * cos(C / 3.0), 1.0, 2.0 * cos(A / 3.0)),
			pF = trilinear_to_cartesian(2.0 * cos(B / 3.0), 2.0 * cos(A / 3.0), 1.0);
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n", pD.x_, pD.y_, pE.x_, pE.y_, pF.x_, pF.y_);
	}
	return 0;
}

