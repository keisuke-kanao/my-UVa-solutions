
/*
	UVa 12049 - Just Prune The List

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12049_Just_Prune_The_List.cpp
*/

#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;

void read_integers(int n, map<int, int>& m)
{
	for (int i = 0; i < n; i++) {
		int j;
		cin >> j;
		pair<map<int, int>::iterator, bool> result = m.insert(make_pair(j, 1));
		if (!result.second)
			result.first->second++;
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		map<int, int> first, second; // key are integers, valuesa are their occurrences
		read_integers(n, first);
		read_integers(m, second);
		int nr_removed = 0;
		map<int, int>::const_iterator fi = first.begin(), fe = first.end();
		map<int, int>::const_iterator si = second.begin(), se = second.end();
		while (fi != fe && si != se) {
			if (fi->first < si->first) {
				nr_removed += fi->second;
				++fi;
			}
			else if (fi->first > si->first) {
				nr_removed += si->second;
				++si;
			}
			else {
				nr_removed += abs(fi->second - si->second);
				++fi; ++si;
			}
		}
		for (; fi != fe; ++fi)
			nr_removed += fi->second;
		for (; si != se; ++si)
			nr_removed += si->second;
		cout << nr_removed << endl;
	}
	return 0;
}

