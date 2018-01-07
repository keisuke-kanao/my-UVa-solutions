
/*
	UVa 152 - Tree's a Crowd

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_152_Trees_a_Crowd.cpp
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

const int nr_trees_max = 5000, nr_dimensions = 3;

struct tree_comparator
{
	int index_;
	tree_comparator(int index) : index_(index) {}
	bool operator() (const vector<int>& i, const vector<int>& j) const {return i[index_] < j[index_];}
};

double tree_distance(const vector<int>& i, const vector<int>& j)
{
	double d = 0.0;
	for (int k = 0; k < nr_dimensions; k++)
		d += (i[k] - j[k]) * (i[k] - j[k]);
	return sqrt(d);
}

int main()
{
	vector< vector<int> > trees(nr_trees_max, vector<int>(nr_dimensions));
	int n = 0;
	for ( ; ; n++) {
		int x, y, z;
		cin >> x >> y >> z;
		if (!x && !y && !z)
			break;
		trees[n][0] = x; trees[n][1] = y; trees[n][2] = z;
	}
	trees.resize(n);
	for (int i = 0; i < nr_dimensions; i++)
		stable_sort(trees.begin(), trees.end(), tree_comparator(i));
	const int nr_bins = 10;
	vector<int> histogram(nr_bins, 0);
	for (int i = 0; i < n; i++) {
		const vector<int>& t = trees[i];
		int d = numeric_limits<int>::max();
		for (int j = 0; j < nr_dimensions; j++) {
			for (int k = i - 1; k >= 0 && trees[k][j] >= t[j] - 10; k--)
				d = min(d, static_cast<int>(tree_distance(t, trees[k])));
			for (int k = i + 1; k < n && trees[k][j] <= t[j] + 10; k++)
				d = min(d, static_cast<int>(tree_distance(t, trees[k])));
		}
		if (d < 10)
			histogram[d]++;
	}
	for (int i = 0; i < nr_bins; i++)
		cout << setw(4) << setfill(' ') << histogram[i];
	cout << endl;
	return 0;
}

