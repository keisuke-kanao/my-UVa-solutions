
/*
	UVa 273 - Jack Straws

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_273_Jack_Straws.cpp
*/

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
using namespace std;

#define EPSILON numeric_limits<float>::epsilon()

struct point {
	double x, y;
};

struct line {
	double a; // x-coefficient
	double b; // y-coefficient
	double c; // constant term
};

struct line_segment {
	point p1, p2;
};

void points_to_line(const point& p1, const point& p2, line& l)
{
	if (fabs(p1.x - p2.x) <= EPSILON) {
		l.a = 1; l.b = 0; l.c = -p1.x;
	}
	else {
		l.b = 1;
		l.a = -(p1.y - p2.y)/(p1.x - p2.x);
		l.c = -(l.a * p1.x) - l.b * p1.y;
	}
}

bool parallelQ(const line& l1, const line& l2)
{
	return fabs(l1.a - l2.a) <= EPSILON && fabs(l1.b - l2.b) <= EPSILON;
}

bool same_lineQ(const line& l1, const line& l2)
{
	return parallelQ(l1, l2) && fabs(l1.c - l2.c) <= EPSILON;
}

bool point_in_box(const point& p, const point& b1, const point& b2)
{
	return p.x >= min(b1.x, b2.x) - EPSILON && p.x <= max(b1.x, b2.x) + EPSILON &&
		p.y >= min(b1.y, b2.y)- EPSILON && p.y <= max(b1.y, b2.y) + EPSILON;
}

bool intersection_point(const line& l1, const line& l2, point& p)
{
	if (same_lineQ(l1, l2))
		return false;
	if (parallelQ(l1, l2))
		return false;
	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (fabs(l1.b) > EPSILON) // test for vertical line
		p.y = - (l1.a * p.x + l1.c) / l1.b;
	else
		p.y = - (l2.a * p.x + l2.c) / l2.b;
	return true;
}

bool line_segments_intersect(const line_segment& s1, const line_segment& s2)
{
	line l1, l2;
	points_to_line(s1.p1, s1.p2, l1);
	points_to_line(s2.p1, s2.p2, l2);
	if (same_lineQ(l1, l2)) // overlapping or disjoint segments
		return point_in_box(s1.p1, s2.p1, s2.p2) || point_in_box(s1.p2, s2.p1, s2.p2);
	if (parallelQ(l1, l2))
		return false;
	point p;
	intersection_point(l1, l2, p);
	return point_in_box(p, s1.p1, s1.p2) && point_in_box(p, s2.p1, s2.p2);
}

class union_find {
public:
	union_find(int n);
	~union_find() {}
	int find(int i) const;
	int do_union(int i, int j);
		// generate the union of the two sets to which i and j belong and return the representative of the result set
	int nr_sets() const {return s_;}

private:
	int n_; // number of elements
	int s_; // number of sets
	vector<int> representatives_; // representatives[i] is the representative of a set to which i belongs
	vector<int> ranks_; // ranks_[i] is the number of elements in the set to which i belongs
};

union_find::union_find(int n)
	: n_(n), s_(n), representatives_(n), ranks_(n, 1)
{
	for (int i = 0; i < n_; i++)
		representatives_[i] = i;
}

int union_find::find(int i) const // return the representative of a set to which i belongs
{
	return (representatives_[i] == i) ? i : find(representatives_[i]);
}

int union_find::do_union(int i, int j)
// generate the union of the two sets to which i and j belong and return the representative of the result set
{
	int ri = find(i), rj = find(j);
	if (ri == rj) // already in the same set
		return -1;
	s_--;
	if (ranks_[ri] >= ranks_[rj]) {
		ranks_[ri] += ranks_[rj];
		representatives_[rj] = ri;
		return ri;
	}
	else {
		ranks_[rj] += ranks_[ri];
		representatives_[ri] = rj;
		return rj;
	}
}

int main()
{
	const int n_max = 32;
	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		line_segment lss[n_max];
		for (int i = 0; i < n; i++)
			cin >> lss[i].p1.x >> lss[i].p1.y >> lss[i].p2.x >> lss[i].p2.y;
		union_find uf(n);
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				if (line_segments_intersect(lss[i], lss[j]))
					uf.do_union(i, j);
		while (true) {
			int a, b;
			cin >> a >> b;
			if (!a && !b)
				break;
			cout << ((uf.find(a - 1) == uf.find(b - 1)) ? "CONNECTED\n" : "NOT CONNECTED\n");
		}
		if (tc)
			cout << endl;
	}
	return 0;
}

