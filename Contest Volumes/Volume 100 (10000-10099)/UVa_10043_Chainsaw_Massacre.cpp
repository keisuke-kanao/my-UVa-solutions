
/*
	14.7.3 Chainsaw Massacre
	PC/UVa IDs: 111403/10043, Popularity: B, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10043_Chainsaw_Massacre.cpp
*/

/*
	This is an application of maximum (or largest) empty rectangle problem.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

struct point {
	int x, y;

	point() : x(0), y(0) {}
	point(int _x, int _y) : x(_x), y(_y) {}
	point(const point &p) : x(p.x), y(p.y) {}
	bool operator==(const point& p) const {return x == p.x && y == p.y;}
};

bool left_lower_order(const point& p1, const point& p2)
{
	if (p1.x < p2.x)
		return true;
	else if (p1.x > p2.x)
		return false;
	else if (p1.y < p2.y)
		return true;
	else
		return false;
}

bool upper_order(const point& p1, const point& p2)
{
	return p1.y > p2.y;
}

int maximum_empty_rectangle(int l, int w, vector<point>& points)
{
	if (points.empty())
		return l * w;
	sort(points.begin(), points.end(), left_lower_order); // sort the points in leftmost-lowest order
	for (vector<point>::iterator i = points.begin(); i != points.end(); ) { // remove the duplicate points
		vector<point>::iterator j = i;
		j++;
		if (j != points.end() && *i == *j)
			i = points.erase(i);
		else
			i++;
	}
	int n = points.size();
	// get the maximum gap between the x coordinates
	vector<point>::const_iterator i = points.begin();
	int mgap = i->x;
	for (i++; i != points.end(); i++)
		mgap = max(mgap, i->x - (i - 1)->x);
	mgap = max(mgap, l - (i - 1)->x);
	int maxr = mgap * w;
	sort(points.begin(), points.end(), upper_order); // sort the points in descending order of y coordinates
	for (vector<point>::const_iterator i = points.begin(); i != points.end(); i++) {
		int tl = 0, tr = l;
		vector<point>::const_iterator j = i;
		for (j++; j != points.end(); j++)
			if (j->x > tl && j->x < tr) {
				maxr = max(maxr, (tr - tl) * (i->y - j->y));
				if (j->x > i->x)
					tr = j->x;
				else
					tl = j->x;
			}
		maxr = max(maxr, (tr - tl) * i->y);
	}
	for (vector<point>::const_reverse_iterator i = points.rbegin(); i != points.rend(); i++) {
		int li = 0, ri = l;
		vector<point>::const_reverse_iterator j = i;
		for (j++; j != points.rend(); j++)
			// since points are sorted in descending order of y coordinates, j->y >= i->y
			if (j->y > i->y) {
				if (j->x > i->x)
					ri = min(ri, j->x);
				else
					li = max(li, j->x);
			}
		maxr = max(maxr, (ri - li) * (w - i->y));
	}
	return maxr;
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int nr_scenarios;
	cin >> nr_scenarios;
	while (nr_scenarios--) {
		vector<point> points;
		int l, w;
		cin >> l >> w;
		while (true) {
			int k;
			cin >> k;
			if (!k) // end of a scenario
				break;
			int x, y, dx = 0, dy = 0;
			cin >> x >> y;
			if (k > 1)
				cin >> dx >> dy;
			for ( ; k; k--, x += dx, y += dy)
				points.push_back(point(x, y));
		}
		cout << maximum_empty_rectangle(l, w, points) << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

