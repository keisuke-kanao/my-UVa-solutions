
/*
	UVa 10660 - Citizen attention offices

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10660_Citizen_attention_offices.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int nr_rows = 5, nr_columns = 5, nr_areas = nr_rows * nr_columns, nr_offices = 5;

struct area {
	int i_;
	int p_;
};

area areas[nr_areas];
int area_indices[nr_offices], min_d_offices[nr_offices];

int get_distance(int i, int j)
{
	int ri = i / nr_columns, ci = i % nr_columns, rj = j / nr_columns, cj = j % nr_columns;
	return abs(ri - rj) + abs(ci - cj);
}

void calculate_distances(int n, int ai, int k, int& min_d)
{
	if (k < nr_offices) {
		for (int i = ai; i < nr_areas; i++) {
			area_indices[k] = i;
			calculate_distances(n, i + 1, k + 1, min_d); // recursively generate the combinations of indices from (ai + 1) to (n - 1)
		}
	}
	else {
		int d = 0;
		for (int i = 0; i < n; i++) {
			int min_d_i = numeric_limits<int>::max();
			for (int j = 0; j < nr_offices; j++)
				min_d_i = min(min_d_i, get_distance(area_indices[j], areas[i].i_) * areas[i].p_);
			d += min_d_i;
		}
		if (d < min_d) {
			min_d = d;
#ifdef DEBUG
			printf("%d: ", min_d);
#endif
			for (int i = 0; i < nr_offices; i++) {
#ifdef DEBUG
				printf("%d%c", area_indices[i], ((i < nr_offices - 1) ? ' ' : '\n'));
#endif
				min_d_offices[i] = area_indices[i];
			}
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int r, c;
			scanf("%d %d %d", &r, &c, &areas[i].p_);
			areas[i].i_ = r * nr_columns + c;
		}
		// generate all combinations of n areas taken 5 at a time, starting with combinations containing 0 in the first position
		int min_d = numeric_limits<int>::max();
		calculate_distances(n, 0, 0, min_d);
		for (int i = 0; i < nr_offices; i++)
			printf("%d%c", min_d_offices[i], ((i < nr_offices - 1) ? ' ' : '\n'));
	}
	return 0;
}

