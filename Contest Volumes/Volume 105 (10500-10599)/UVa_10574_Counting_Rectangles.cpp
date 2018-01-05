
/*
	UVa 10574 - Counting Rectangles

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10574_Counting_Rectangles.cpp

	This is an accepted solution.
*/

#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	for (int cn = 1; cn <= t; cn++) {
		int n;
		scanf("%d", &n);
		map< int, vector<int> > points;
			// points[i] is the set of y coordinates of points whose x coordinate is i
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			pair<map<int, vector<int> >::iterator, bool> result = points.insert(make_pair(x, vector<int>()));
			result.first->second.push_back(y);
		}
		for (map<int, vector<int> >::iterator xi = points.begin(); xi != points.end(); ) {
			if (xi->second.size() < 2)
				points.erase(xi++);
			else {
				sort(xi->second.begin(), xi->second.end());
				++xi;
			}
		}
		long long nr_rectangles = 0;
		for (map<int, vector<int> >::const_iterator xl = points.begin(), xe = points.end(); xl != xe; ++xl)
			for (map<int, vector<int> >::const_iterator xr = next(xl); xr != xe; ++xr) {
				const vector<int>& yls = xl->second;
				const vector<int>& yrs = xr->second;
				long long nr_ys = 0;
				for (size_t li = 0, le = yls.size(), ri = 0, re = yrs.size(); li < le && ri < re; ) {
					if (yls[li] < yrs[ri])
						li++;
					else if (yls[li] > yrs[ri])
						ri++;
					else {
						nr_ys++;
						li++, ri++;
					}
				}
				if (nr_ys > 1)
					nr_rectangles += nr_ys * (nr_ys - 1) / 2;
			}
		printf("Case %d: %d\n", cn, nr_rectangles);
	}
	return 0;
}

