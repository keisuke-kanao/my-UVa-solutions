
/*
	UVa 10285 - Longest Run on a Snowboard

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10285_Longest_Run_on_a_Snowboard.map.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

/*
	Let h[i][j] be the height of the grid at row of i and column of j (0 <= i < R, 0 <= j < C), and
	let r[i][j] be the longest run length at row of i and column of j, then;
		r[i][j] = max. {r[i - 1][j] + 1, if (i >= 1 && h[i - 1][j] < h[i][j])
						r[i + 1][j] + 1, if (i < R - 1 && h[i + 1][j] < h[i][j])
						r[i][j - 1] + 1, if (j >= 1 && h[i][j - 1] < h[i][j])
						r[i][j + 1] + 1, if (j < C - 1 && h[i][j + 1] < h[i][j])
					}
*/

const int nr_dirs = 4;

int calculate_longest_run_length(int si, int sj, int r, int c, const vector< vector<int> >& heights,
	map< pair<int, int>, int>& cache)
{
	map< pair<int, int>, int>::iterator ci = cache.find(make_pair(si, sj));
	if (ci != cache.end())
		return ci->second;
	int h = heights[si][sj];
	const pair<int, int> dirs[nr_dirs] = {make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1)};
	int run_lengths[nr_dirs];
	for (int i = 0; i < nr_dirs; i++) {
		int di = si + dirs[i].first, dj = sj + dirs[i].second;
		run_lengths[i] = (di >= 0 && di < r && dj >= 0 && dj < c && heights[di][dj] < h) ?
			calculate_longest_run_length(di, dj, r, c, heights, cache) : 0;
	}
	int max_run_length = *max_element(run_lengths, run_lengths + nr_dirs) + 1;
	cache.insert(make_pair(make_pair(si, sj), max_run_length));
	return max_run_length;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
#ifdef __ELAPSED_TIME__
	time_t start = clock();
#endif
	while (nr_cases--) {
		string name;
		int r, c;
		cin >> name >> r >> c;
		vector< vector<int> > heights(r, vector<int>(c));
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				cin >> heights[i][j];
		map< pair<int, int>, int> cache;
			// key is the position in an area, value is its longest run length
		int max_run_length = 0;
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				max_run_length = max(max_run_length,
					calculate_longest_run_length(i, j, r, c, heights, cache));
		cout << name << ": " << max_run_length << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

