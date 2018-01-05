
/*
	UVa 10102 - The path in the colored field

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10102_The_path_in_the_colored_field.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main()
{
	int m;
	while (cin >> m) {
		vector< pair<int, int> > ones, threes;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++) {
				char c;
				cin >> c;
				if (c == '1')
					ones.push_back(make_pair(i, j));
				else if (c == '3')
					threes.push_back(make_pair(i, j));
			}
		int max_path = 0;
		for (vector< pair<int, int> >::const_iterator oi = ones.begin(), oe = ones.end(); oi != oe; ++oi) {
			int min_path = m * m;
			for (vector< pair<int, int> >::const_iterator ti = threes.begin(), te = threes.end(); ti != te; ++ti)
				min_path = min(min_path, abs(oi->first - ti->first) + abs(oi->second - ti->second));
			max_path = max(max_path, min_path);
		}
		cout << max_path << endl;
	}
	return 0;
}

