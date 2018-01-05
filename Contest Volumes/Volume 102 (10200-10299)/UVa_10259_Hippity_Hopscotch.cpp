
/*
	UVa 10259 - Hippity Hopscotch

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10259_Hippity_Hopscotch.cpp

	from Waterloo Programming Contests, 4 October 1998, Problem A
		(http://acm.student.cs.uwaterloo.ca/~acm00/98oct4/data/)
*/

#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 100;
int grid[n_max][n_max], visited[n_max][n_max];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	const int nr_dirs = 4;
	const pair<int, int> dirs[nr_dirs] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};
	int t;
	cin >> t;
	while (t--) {
		int n, k;
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> grid[i][j];
				visited[i][j] = 0;
			}
		queue< pair<int, int> > q;
		visited[0][0] = grid[0][0];
		int max_nr = 0;
		q.push(make_pair(0, 0));
		while (!q.empty()) {
			pair<int, int> u = q.front(); q.pop();
			int p = grid[u.first][u.second], nr = visited[u.first][u.second];
			max_nr = max(max_nr, nr);
			for (int i = 0; i < nr_dirs; i++)
				for (int j = 1; j <= k; j++) {
					int r = u.first + dirs[i].first * j, c = u.second + dirs[i].second * j;
					if (r >= 0 && r < n && c >= 0 && c < n &&
						grid[r][c] > p && visited[r][c] < grid[r][c] + nr) {
						visited[r][c] = grid[r][c] + nr;
						q.push(make_pair(r, c));
					}
				}
		}
		cout << max_nr << endl;
		if (t)
			cout << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

