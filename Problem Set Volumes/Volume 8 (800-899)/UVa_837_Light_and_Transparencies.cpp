
/*
	UVa 837 - Light and Transparencies

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_837_Light_and_Transparencies.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct point {
	double x_;
	int tci_; // index to tcs[]
};

struct tc { // transparent coeficients
	bool effective_;
	double r_;
};

bool compare_point(const point& p, const point& q)
{
	return p.x_ < q.x_;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int nl;
		cin >> nl;
		int np = nl * 2;
		vector<point> points(np);
		vector<tc> tcs(nl);
		for (int i = 0; i < nl; i++) {
			double y1, y2;
			cin >> points[i * 2].x_ >> y1 >> points[i * 2 + 1].x_ >> y2 >> tcs[i].r_;
			points[i * 2].tci_ = points[i * 2 + 1].tci_ = i;
			tcs[i].effective_ = false;
		}
		sort(points.begin(), points.end(), compare_point);
		cout << np + 1 << endl;
		cout << fixed;
		for (int i = 0; i <= np; i++) {
			if (i)
				cout << setprecision(3) << points[i - 1].x_;
			else
					cout << "-inf";
			if (i < np)
					cout << ' ' << setprecision(3) << points[i].x_;
			else
				cout << " +inf";
			double pl = 1.0; // percentage of light
			if (i && i < np) {
				for (int j = 0; j < nl; j++)
					if (tcs[j].effective_)
						pl *= tcs[j].r_;
			}
			cout << ' ' << setprecision(3) << pl << endl;
			if (i < np)
				tcs[points[i].tci_].effective_ = !tcs[points[i].tci_].effective_;
		}
		if (t)
			cout << endl;
	}
	return 0;
}

