
/*
	UVa 209 - Triangular Vertices

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_209_Triangular_Vertices.cpp
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
using namespace std;

const int nr_points_max = 6;

struct point {
	int r_, c_;

bool operator<(const point& p) const {return (r_ != p.r_) ? r_ < p.r_ : c_ < p.c_;}
bool operator==(const point& p) const {return r_ == p.r_ && c_ == p.c_;}
} points[nr_points_max];

void get_point(int n, point& p)
{
	int r = static_cast<int>((sqrt(1.0 + 8.0 * n) - 1.0) / 2.0);
	if (r * (r + 1) / 2 < n)
		r++;
	p.r_ = r;
	p.c_ = n - (r - 1) * r / 2;
}

int get_length(const point& p, const point& q)
{
	if (p.r_ == q.r_)
		return abs(p.c_ - q.c_);
	else if (p.c_ == q.c_)
		return abs(p.r_ - q.r_);
	else if (p.c_ - q.c_ == p.r_ - q.r_)
		return abs(p.r_ - q.r_);
	else
		return -1;
}

bool is_triangle()
{
	int a = get_length(points[0], points[1]), b = get_length(points[1], points[2]),
		c = get_length(points[2], points[0]);
	return a > 0 && a == b && b == c;
}

bool is_parallelogram()
{
	int a = get_length(points[0], points[1]), b = get_length(points[2], points[3]),
		c = get_length(points[0], points[2]), d = get_length(points[1], points[3]);
	return a > 0 && a == b && b == c && c == d;
}

bool is_hexagon()
{
	if (points[0].r_ != points[1].r_)
		return false;
	int a = points[1].c_ - points[0].c_;
	if (points[0].c_ != points[2].c_ || a != points[2].r_ - points[0].r_)
		return false;
	if (points[3].c_ > points[1].c_ && points[3].c_ - points[1].c_ == points[3].r_ - points[1].r_ &&
		points[3].c_ - points[1].c_ == a)
		;
	else
		return false;
	if (points[4].c_ > points[2].c_ && points[4].c_ - points[2].c_ == points[4].r_ - points[2].r_ &&
		points[4].c_ - points[2].c_ == a)
		;
	else
		return false;
	if (points[3].c_ != points[5].c_ || a != points[5].r_ - points[3].r_)
		return false;
	if (points[4].r_ != points[5].r_ || points[5].c_ - points[4].c_ != a)
		return false;
	return true;
}

int main()
{
	string s;
	while (getline(cin, s)) {
		istringstream iss(s);
		int p, nr_points = 0;
		for ( ; iss >> p; nr_points++) {
			cout << p << ' ';
			get_point(p, points[nr_points]);
		}
		bool acceptable = false;
		sort(points, points + nr_points);
		int nr_unique = unique(points, points + nr_points) - points;
		if (nr_unique == nr_points && (nr_points == 3 || nr_points == 4 || nr_points == 6)) {
#ifdef DEBUG
			for (int i = 0; i < nr_points; i++)
				cout << '(' << points[i].r_ << ',' << points[i].c_ << ") ";
			cout << endl;
#endif
			if (nr_points == 3) {
				if (acceptable = is_triangle())
					cout << "are the vertices of a triangle\n";
			}
			else if (nr_points == 4) {
				if (acceptable = is_parallelogram())
					cout << "are the vertices of a parallelogram\n";
			}
			else {
				if (acceptable = is_hexagon())
					cout << "are the vertices of a hexagon\n";
			}
		}
		if (!acceptable)
			cout << "are not the vertices of an acceptable figure\n";
	}
	return 0;
}

