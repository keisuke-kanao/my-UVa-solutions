
/*
	UVa 11800 - Determine the Shape

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11800_Determine_the_Shape.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_points = 4;

struct point {
	int x_, y_;

	point() {}
	point(int x, int y) : x_(x), y_(y) {}
	point(const point &p) : x_(p.x_), y_(p.y_) {}
} points[nr_points];

bool left_lower(const point& p, const point& q)
{
	if (p.x_ < q.x_)
		return true;
	else if (p.x_ > q.x_)
		return false;
	else if (p.y_ < q.y_)
		return true;
	else
		return false;
}

int cross_product(const point& o, const point& p, const point& q)
{
	return (p.x_ - o.x_) * (q.y_ - o.y_) - (q.x_ - o.x_) * (p.y_ - o.y_);
}

bool ccw(const point& p, const point& q, const point& r)
{
	// see if the point r is to the left of p -> q (or, p - q - r are counter-clorkwise)
	return cross_product(p, q, r) > 0;
}

struct smaller_angle {
	const point& first;

	smaller_angle(const point& _first) : first(_first) {}
	bool operator() (const point& p, const point& q) const {return ccw(first, p, q);}
};

int square_distance(const point& p, const point& q)
{
	int dx = p.x_ - q.x_, dy = p.y_ - q.y_;
	return dx * dx + dy * dy;
}

bool diagonals_bisect()
{
	return points[0].x_ + points[2].x_ == points[1].x_ + points[3].x_ && points[0].y_ + points[2].y_ == points[1].y_ + points[3].y_;
}

bool diagonals_equal()
{
	return square_distance(points[0], points[2]) == square_distance(points[1], points[3]);
}

bool adjacent_sides_equal()
{
	return square_distance(points[0], points[1]) == square_distance(points[1], points[2]);
}

bool two_line_seguments_parallel(const point& lp, const point& lq, const point& mp, const point& mq)
{
	if (lp.x_ == lq.x_) // vertical line
		return mp.x_ == mq.x_;
	else if (mp.x_ == mq.x_)
		return lp.x_ == lq.x_;
	else
		return (lp.x_ - lq.x_) * (mp.y_ - mq.y_) == (mp.x_ - mq.x_) * (lp.y_ - lq.y_);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		for (int i = 0; i < nr_points; i++)
			scanf("%d %d", &points[i].x_, &points[i].y_);
		sort(points, points + nr_points, left_lower); // sort the points in leftmost-lowest order
		sort(points + 1, points + nr_points, smaller_angle(points[0])); // sort the second and later points in increasing angular order
		printf("Case %d: ", t);
		if (diagonals_bisect()) {
			if (adjacent_sides_equal()) {
				if (diagonals_equal())
					puts("Square");
				else
					puts("Rhombus");
			}
			else if (diagonals_equal())
				puts("Rectangle");
			else
				puts("Parallelogram");
		}
		else if (two_line_seguments_parallel(points[0], points[1], points[2], points[3]) ||
			two_line_seguments_parallel(points[1], points[2], points[3], points[0]))
			puts("Trapezium");
		else
			puts("Ordinary Quadrilateral");
	}
	return 0;
}

