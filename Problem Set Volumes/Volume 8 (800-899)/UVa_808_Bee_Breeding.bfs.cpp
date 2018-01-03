
/*
	UVa 808 - Bee Breeding

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_808_Bee_Breeding.bfs.cpp

	another accepted soluton, ranking = 757.
*/

#include <iostream>
#include <utility>
#include <queue>
#ifdef DEBUG
#include <limits>
#include <algorithm>
#endif
#include <cstring>
#include <cmath>
using namespace std;

/*
	For conversion betwwn cell numbers and hexagonal coordinates, see the solution of Uva 10182 - Bee Maja.
*/

int calculate_layer_number(int m)
{
	double sqrt_d = sqrt(static_cast<double>(3 * (4 * m - 1)));
	return static_cast<int>(ceil((3.0 + sqrt_d) / 6.0));
}

pair<int, int> cell_to_hex(int m)
{
	if (m == 1)
		return make_pair(0, 0);
	else {
		int nr_layer = calculate_layer_number(m); // get the layer number
		int min_n = 3 * (nr_layer - 1) * (nr_layer - 2) + 2; // min. number in the layer
		m -= min_n;
		// the bottom hexagonal is the (layer - 1)-th number in the layer
		m -= nr_layer - 2;
		if (m < 0)
			m += 6 * (nr_layer - 1);
		int x = 0, y = nr_layer - 1;
		for (int i = 0; i < nr_layer - 1 && m; i++, m--)
			x--;
		for (int i = 0; i < nr_layer - 1 && m; i++, m--)
			y--;
		for (int i = 0; i < nr_layer - 1 && m; i++, m--) {
			x++; y--;
		}
		for (int i = 0; i < nr_layer - 1 && m; i++, m--)
			x++;
		for (int i = 0; i < nr_layer - 1 && m; i++, m--)
			y++;
		for (int i = 0; i < nr_layer - 1 && m; i++, m--) {
			x--; y++;
		}
		return make_pair(x, y);
	}
}

const int m_max = 10000;
const int hex_min = -57, hex_max = 58;
bool valid[hex_max - hex_min + 1][hex_max - hex_min + 1];
bool visited[hex_max - hex_min + 1][hex_max - hex_min + 1];

int bfs(pair<int, int> s, pair<int, int> t)
{
	const int nr_dirs = 6;
	const int dirs[nr_dirs][2] = {{0, 1}, {1,0}, {1, -1}, {0, -1}, {-1, 0}, {-1, 1}};
	memset(visited, 0, sizeof(visited));
	queue< pair< pair<int, int>, int > > q;
	visited[s.first - hex_min][s.second - hex_min] = true;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair< pair<int, int>, int > p = q.front();
		q.pop();
		if (p.first == t)
			return p.second;
		for (int k = 0; k < nr_dirs; k++) {
			int x = p.first.first + dirs[k][0], y = p.first.second + dirs[k][1];
			if (x < hex_min || x > hex_max || y < hex_min || y > hex_max ||
				!valid[x - hex_min][y - hex_min] || visited[x - hex_min][y - hex_min])
				;
			else {
				visited[x - hex_min][y - hex_min] = true;
				q.push(make_pair(make_pair(x, y), p.second + 1));
			}
		}
	}
	return -1;
}

int main()
{
#ifdef DEBUG
	int xy_min = numeric_limits<int>::max(), xy_max = numeric_limits<int>::min();
#endif
	for (int m = 1; m <= m_max; m++) {
		pair<int, int> hex_xy = cell_to_hex(m);
		valid[hex_xy.first - hex_min][hex_xy.second - hex_min] = true;
#ifdef DEBUG
		xy_min = min(xy_min, min(hex_xy.first, hex_xy.second));
		xy_max = max(xy_max, max(hex_xy.first, hex_xy.second));
#endif
	}
#ifdef DEBUG
	cout << xy_min << ' ' << xy_max << endl;
#endif
	while (true) {
		int a, b;
		cin >> a >> b;
		if (!a && !b)
			break;
		pair<int, int> ha = cell_to_hex(a), hb = cell_to_hex(b);
		cout << "The distance between cells " << a << " and " << b << " is " << bfs(ha, hb) << ".\n";
	}
	return 0;
}

