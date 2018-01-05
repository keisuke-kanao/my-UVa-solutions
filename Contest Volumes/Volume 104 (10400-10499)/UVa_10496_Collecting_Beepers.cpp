
/*
	UVa 10496 - Collecting Beepers

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10496_Collecting_Beepers.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

struct point {
	int x_, y_;

	point() : x_(0), y_(0) {}
	point(int x, int y) : x_(x), y_(y) {}
	static int distance(const point& p1, const point& p2)
		{return abs(p1.x_ - p2.x_) + abs(p1.y_ - p2.y_);}
};

struct beeper_distance {
	const point& p_;

	beeper_distance(const point& p) : p_(p) {}
	bool operator() (const point& p1, const point& p2) const
		{return point::distance(p_, p1) < point::distance(p_, p2);}
};

void collect_beepers(int n, int ci, int pi, const point& sp, const vector<point>& beepers,
	vector<bool> collected, int path, int& shortest_path)
{
	if (ci == n) {
		path += point::distance(beepers[pi], sp);
#ifdef DEBUG
		cout << path << endl;
#endif
		if (path < shortest_path)
			shortest_path = path;
	}
	else {
		for (int i = 0; i < n; i++) {
			if (collected[i])
				continue;
			int d = (ci) ? point::distance(beepers[pi], beepers[i]) : point::distance(sp, beepers[i]);
			if (path + d < shortest_path) {
				collected[i] = true;
				collect_beepers(n, ci + 1, i, sp, beepers, collected, path + d, shortest_path);
				collected[i] = false;
			}
		}
	}
}

int main()
{
	int ns;
	cin >> ns;
	while (ns--) {
		int wx, wy;
		cin >> wx >> wy;
		point sp;
		cin >> sp.x_ >> sp.y_;
		int n;
		cin >> n;
		vector<point> beepers(n);
		for (int i = 0; i < n; i++)
			cin >> beepers[i].x_ >> beepers[i].y_;
		sort(beepers. begin(), beepers.end(), beeper_distance(sp));
			// sort the beepers in ascending order of the distance from the starting point
		vector<bool> collected(n, false);
		int shortest_path = n * wx * wy;
		collect_beepers(n, 0, -1, sp, beepers, collected, 0, shortest_path);
		cout << "The shortest path has length " << shortest_path << endl;
	}
	return 0;
}

