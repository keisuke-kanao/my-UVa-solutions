
/*
	UVa 11094 - Continents

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11094_Continents.cpp
*/

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

const int m_max = 20, n_max = 20;
char region_map[m_max][n_max];

int bfs(int i, int j, int m, int n)
{
	int nr = 0;
	const int nr_dirs = 4;
	const int dirs[nr_dirs][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	queue< pair<int, int> > q;
	char c = region_map[i][j];
	nr++;
	region_map[i][j] = 0;
	q.push(make_pair(i, j));
	while (!q.empty()) {
		pair<int, int> p = q.front();
		q.pop();
		for (int k = 0; k < nr_dirs; k++) {
			i = p.first + dirs[k][0]; j = p.second + dirs[k][1];
			if (j < 0)
				j = n - 1;
			else if (j >= n)
				j = 0;
			if (i < 0 || i >= m || region_map[i][j] != c)
				;
			else {
				nr++;
				region_map[i][j] = 0;
				q.push(make_pair(i, j));
			}
		}
	}
	return nr;
}

int main()
{
	int m, n;
	while (cin >> m >> n) {
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				cin >> region_map[i][j];
		int x, y;
		cin >> x >> y;
		char land_letter = region_map[x][y];
		bfs(x, y, m, n);
		int max_region = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (region_map[i][j] == land_letter)
					max_region = max(max_region, bfs(i, j, m, n));
		cout << max_region << endl;
	}
	return 0;
}

