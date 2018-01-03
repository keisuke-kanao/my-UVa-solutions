
/*
	UVa 988 - Many Paths, One Destination

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_988_Many_Paths_One_Destination.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

int count_events(int i, const vector< vector<int> >& paths, vector<int>& nr_ways)
{
	if (nr_ways[i] != -1)
		return nr_ways[i];
	else if (paths[i].empty())
		return nr_ways[i] = 1;
	else {
		int nr = 0;
		for (size_t j = 0, k = paths[i].size(); j < k; j++)
			nr += count_events(paths[i][j], paths, nr_ways);
		return nr_ways[i] = nr;
	}
}

int main()
{
	int n;
	bool printed = false;
	while (cin >> n) {
		if (printed)
			cout << endl;
		else
			printed = true;
		vector< vector<int> > paths(n);
		for (int i = 0; i < n; i++) {
			int j;
			cin >> j;
			while (j--) {
				int k;
				cin >> k;
				paths[i].push_back(k);
			}
		}
		vector<int> nr_ways(n, -1);
			// nr_ways[i] is the number of ways from i-th event
		cout << count_events(0, paths, nr_ways) << endl;
	}
	return 0;
}

