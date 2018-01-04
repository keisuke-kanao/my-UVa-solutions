
/*
	UVa 484 - The Department of Redundancy Department

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_484_The_Department_of_Redundancy_Department.cpp
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main()
{
	map<int, int> integers; // key is an integer, value is its index to occurrences
	vector< pair<int, int> > occurrences;
		// occurrences[].first is an integer, occurrences[].first is its number of occurrences
	int i, nr_occurrences = 0;
	while (cin >> i) {
		pair<map<int, int>::iterator, bool> result = integers.insert(make_pair(i, nr_occurrences));
		if (result.second) {
			occurrences.push_back(make_pair(i, 1));
			nr_occurrences++;
		}
		else
			occurrences[result.first->second].second++;
	}
	for (vector< pair<int, int> >::const_iterator ci = occurrences.begin(), ce = occurrences.end(); ci != ce; ++ci)
		cout << ci->first << ' ' << ci->second << endl;
	return 0;
}

