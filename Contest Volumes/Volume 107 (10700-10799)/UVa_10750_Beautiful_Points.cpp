
/*
	UVa 10750 - Beautiful Points

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10750_Beautiful_Points.cpp
*/

#include <algorithm>
#include <set>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

const double infinite = numeric_limits<double>::max();
const int N_max = 10000;

/*
pair<double, double> points[N_max];

bool compare_x(const pair<double, double>& i, const pair<double, double>& j)
{
	return i.second < j.second;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &points[i].second, &points[i].first);
		sort(points, points + N, compare_x);
		double closest = infinite;
		pair< pair<double, double>, pair<double, double> > closest_points;
		set< pair<double, double> > sp;
		sp.insert(points[0]);
		for (int pi = 0, i = 1; i < N; i++) {
			for ( ; pi < i && points[i].second - points[pi].second > closest; pi++)
				sp.erase(points[pi]);
			for (set< pair<double, double> >::iterator spi = lower_bound(sp.begin(), sp.end(), make_pair(points[i].first - closest, points[i].second - closest));
				spi != sp.end() && spi->first <= points[i].first + closest; spi++) {
				double d = hypot(points[i].first - spi->first, points[i].second - spi->second);
				if (d < closest) {
					closest = d;
					closest_points = make_pair(*spi, points[i]);
				}
			}
			sp.insert(points[i]);
		}
#ifdef DEBUG
		printf("%.3lf %.3lf %.3lf\n", (closest_points.first.second + closest_points.second.second) / 2.0,
			(closest_points.first.first + closest_points.second.first) / 2.0, closest);
#else
		printf("%.3lf %.3lf\n", (closest_points.first.second + closest_points.second.second) / 2.0,
			(closest_points.first.first + closest_points.second.first) / 2.0);
#endif
		if (t)
			putchar('\n');
	}
	return 0;
}
*/

struct point {
	double x_, y_;
	point() {}
	point(int x, int y) : x_(x), y_(y) {}
	bool operator<(const point& p) const {return x_ < p.x_;}
} points[N_max];

struct point_comparator {
	bool operator() (const point& pi, const point& pj) const
	{
		return (pi.y_ != pj.y_) ? pi.y_ < pj.y_ : pi.x_ < pj.x_;
	}
};

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%lf %lf", &points[i].x_, &points[i].y_);
		sort(points, points + N);
		double closest = infinite;
		pair<point, point> closest_points;
		set<point, point_comparator> sp;
		sp.insert(points[0]);
		for (int pi = 0, i = 1; i < N; i++) {
			for ( ; pi < i && points[i].x_ - points[pi].x_ > closest; pi++)
				sp.erase(points[pi]);
			point p(points[i].x_ - closest, points[i].y_ - closest);
			for (set<point, point_comparator>::iterator spi = lower_bound(sp.begin(), sp.end(), p);
				spi != sp.end() && spi->y_ <= points[i].y_ + closest; ++spi) {
				double d = hypot(points[i].x_ - spi->x_, points[i].y_ - spi->y_);
				if (d < closest) {
					closest = d;
					closest_points = make_pair(*spi, points[i]);
				}
			}
			sp.insert(points[i]);
		}
#ifdef DEBUG
		printf("%.3lf %.3lf %.3lf\n", (closest_points.first.x_ + closest_points.second.x_) / 2.0,
			(closest_points.first.y_ + closest_points.second.y_) / 2.0, closest);
#else
		printf("%.3lf %.3lf\n", (closest_points.first.x_ + closest_points.second.x_) / 2.0,
			(closest_points.first.y_ + closest_points.second.y_) / 2.0);
#endif
		if (t)
			putchar('\n');
	}
	return 0;
}

/*

2
4
0 0
0 1
1 1
1 0
4
-1 -1
0 0
1 0
2 1

Sample Output

0.500 0.000

0.500 0.000

*/

