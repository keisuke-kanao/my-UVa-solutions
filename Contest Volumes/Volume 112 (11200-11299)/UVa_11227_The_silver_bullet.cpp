
/*
	UVa 11227 - The silver bullet.

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11227_The_silver_bullet.cpp
*/

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

const double epsilon = numeric_limits<double>::epsilon();

struct point {
	double x_, y_;

	bool operator==(const point& p) const {return fabs(x_ - p.x_) <= epsilon && fabs(y_ - p.y_) <= epsilon;}
	bool operator<(const point& p) const {
		return (x_ != p.x_) ? x_ < p.x_ : y_ < p.y_;
	}
};

struct line {
	double a_; // x-coefficient
	double b_; // y-coefficient
	double c_; // constant term

	bool operator<(const line& l) const {
		if (a_ != l.a_)
			return a_ < l.a_;
		else if (b_ != l.b_)
			return b_ < l.b_;
		else
			return c_ < l.c_;
	}
};

void points_to_line(const point& p1, const point& p2, line& l)
{
	if (fabs(p1.x_ - p2.x_) <= epsilon) {
		l.a_ = 1.0; l.b_ = 0; l.c_ = -p1.x_;
	}
	else {
		l.b_ = 1.0;
		l.a_ = -(p1.y_ - p2.y_) / (p1.x_ - p2.x_);
		l.c_ = -(l.a_ * p1.x_) - l.b_ * p1.y_;
	}
}

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;
		vector<point> points(N);
		for (int i = 0; i < N; i++)
			cin >> points[i].x_ >> points[i].y_;
		sort(points.begin(), points.end());
		for (vector<point>::iterator pi = points.begin(); pi != points.end(); ) { // remove the duplicate points
			vector<point>::iterator pj = pi;
			++pj;
			if (pj != points.end() && *pi == *pj)
				pi = points.erase(pi);
			else
				++pi;
		}
		size_t n = points.size();
		map< line, set<point> > lines;
		for (size_t i = 0; i < n - 1; i++)
			for (size_t j = i + 1; j < n; j++) {
				line l;
				points_to_line(points[i], points[j], l);
				pair< map< line, set<point> >::iterator, bool > result = lines.insert(make_pair(l, set<point>()));
				result.first->second.insert(points[i]);
				result.first->second.insert(points[j]);
			}
		cout << "Data set #" << t;
		if (n > 1) {
			size_t aligned_max = 0;
			for (map< line, set<point> >::const_iterator li = lines.begin(), le = lines.end(); li != le; ++li)
				aligned_max = max(aligned_max, li->second.size());
			cout << " contains " << n << " gnus, out of which a maximum of " << aligned_max << " are aligned.\n";
		}
		else
			cout << " contains a single gnu.\n";
	}
}

