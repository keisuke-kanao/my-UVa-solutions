
/*
	UVa 949 - Getaway

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_949_Getaway.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <limits>
using namespace std;

int main()
{
	const int nr_dirs = 4;
	pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(-1, 0), make_pair(0, 1), make_pair(0, -1)};
	int nr, nc;
	while (cin >> nr >> nc) {
		int r;
		cin >> r;
		set< pair< pair<int, int>, pair<int, int> > > restrictions;
		while (r--) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			restrictions.insert(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
		}
		int m;
		cin >> m;
		set< pair<pair<int, int>, int> > monitorizations;
		while (m--) {
			int t, x, y;
			cin >> t >> x >> y;
			monitorizations.insert(make_pair(make_pair(x, y), t));
		}
		queue< pair<pair<int, int>, int> > q;
		vector< vector<int> > arrived(nr, vector<int>(nc, numeric_limits<int>::max()));
		int t = 0;
		while (monitorizations.find(make_pair(make_pair(0, 0), t)) != monitorizations.end())
			t++;
		arrived[0][0] = t;
		q.push(make_pair(make_pair(0, 0), t));
		while (!q.empty()) {
			pair<pair<int, int>, int> u = q.front(); q.pop();
			int ux = u.first.first, uy = u.first.second, ut = u.second;
			for (int i = 0; i < nr_dirs; i++) {
				int x = ux + dirs[i].first, y = uy + dirs[i].second;
				if (x >= 0 && x < nr && y >= 0 && y < nc &&
					restrictions.find(make_pair(make_pair(ux, uy), make_pair(x, y))) == restrictions.end()) {
					int t = ut + 1;
					while (monitorizations.find(make_pair(make_pair(x, y), t)) != monitorizations.end())
						t++;
					if (t < arrived[x][y]) {
						arrived[x][y] = t;
						q.push(make_pair(make_pair(x, y), t));
					}
				}
			}
		}
		cout << arrived[nr - 1][nc - 1] << endl;
	}
	return 0;
}

