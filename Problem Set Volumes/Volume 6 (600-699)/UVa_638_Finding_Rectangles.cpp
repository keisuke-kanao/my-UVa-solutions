
/*
	UVa 638 - Finding Rectangles

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_638_Finding_Rectangles.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int n_max = 26, nr_rectangle_points = 4, nr_rectangles_max = 358800 /* 26 * 25 * 24 * 23 */;

struct point {
	char label_[2];
	int x_, y_;
} points[n_max];

int nr_rectangles;

struct rectangle {
	char labels_[nr_rectangle_points + 1];
} rectangles[nr_rectangles_max];

double euclidean_distance(const point& a, const point& b)
{
	double dx = static_cast<double>(a.x_ - b.x_), dy = static_cast<double>(a.y_ - b.y_);
	return sqrt(dx * dx + dy * dy);
}

bool left_lower(int i, int j)
{
	const point& a = points[i];
	const point& b = points[j];
	if (a.x_ < b.x_)
		return true;
	else if (a.x_ > b.x_)
		return false;
	else if (a.y_ < b.y_)
		return true;
	else
		return false;
}

int cross_product(const point& o, const point& a, const point& b)
{
	return (a.x_ - o.x_) * (b.y_ - o.y_) - (b.x_ - o.x_) * (a.y_ - o.y_);
}

struct smaller_angle {
	const point& first_;

	smaller_angle(int fi) : first_(points[fi]) {}
	bool operator() (int i, int j);
};

bool smaller_angle::operator() (int i, int j)
{
	const point& a = points[i];
	const point& b = points[j];
	int cp = cross_product(first_, a, b);
	if(!cp)
		return euclidean_distance(first_, a) < euclidean_distance(first_, b);
	else
		return cp > 0;
}

void find_rectangle(int pis[nr_rectangle_points])
{
	// sort the point indicess
	sort(pis, pis + nr_rectangle_points, left_lower);
	// sort the second and later point indices in increasing angular order
	sort(pis + 1, pis + nr_rectangle_points, smaller_angle(pis[0]));
	const point& lower_left = points[pis[0]];
	const point& lower_right = points[pis[1]];
	const point& upper_right = points[pis[2]];
	const point& upper_left = points[pis[3]];
	if (lower_left.y_ == lower_right.y_ && lower_right.x_ == upper_right.x_ &&
		upper_right.y_ == upper_left.y_ && upper_left.x_ == lower_left.x_) {
		rectangles[nr_rectangles].labels_[0] = upper_left.label_[0], rectangles[nr_rectangles].labels_[1] = upper_right.label_[0],
		rectangles[nr_rectangles].labels_[2] = lower_right.label_[0], rectangles[nr_rectangles].labels_[3] = lower_left.label_[0];
		nr_rectangles++;
	}
}

bool compare_rectangle(const rectangle& ri, const rectangle& rj)
{
	return strcmp(ri.labels_, rj.labels_) < 0;
}

int main()
{
	for (int ps = 1; ; ps++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			scanf("%s %d %d", points[i].label_, &points[i].x_, &points[i].y_);
		int pis[nr_rectangle_points];
		nr_rectangles = 0;
		for (int i = 0; i < n - 3; i++)
			for (int j = i + 1; j < n - 2; j++)
				for (int k  = j + 1; k < n - 1; k++)
					for (int l = k + 1; l < n; l++) {
						pis[0] = i, pis[1] = j, pis[2] = k, pis[3] = l;
						find_rectangle(pis);
					}
		if (nr_rectangles) {
			sort(rectangles, rectangles + nr_rectangles, compare_rectangle);
			printf("Point set %d:\n", ps);
			for (int i = 0; i < nr_rectangles; i++) {
				printf(" %s", rectangles[i].labels_);
				if (i % 10 == 9 || i == nr_rectangles - 1)
					putchar('\n');
			}
		}
		else
			printf("Point set %d: No rectangles\n", ps);
	}
	return 0;
}

