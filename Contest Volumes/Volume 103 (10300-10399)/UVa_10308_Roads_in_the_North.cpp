
/*
	UVa 10308 - Roads in the North

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10308_Roads_in_the_North.cpp

	An accepsted solution.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

const int nr_villages_max = 10000;

vector< vector< pair<int, int> > > roads(nr_villages_max + 1);
	// roads[i].first is the number of village adjacent to the village i
	// roads[i].second is the length of road between the village i and roads[i].first

int dfs(int v, int pv, int& diameter)
{
	int max_d = 0, second_max_d = 0;
	for (vector< pair<int, int> >::const_iterator i = roads[v].begin(), e = roads[v].end(); i != e; ++i) {
		if (i->first == pv)
			continue;
		int d = i->second + dfs(i->first, v, diameter);
		if (d > max_d) {
			second_max_d = max_d; max_d = d;
		}
		else if (d > second_max_d)
			second_max_d = d;
	}
	diameter = max(diameter, max_d + second_max_d);
	return max_d;
}

int main()
{
	int nr_villages = 0;
	string line;
	do {
		getline(cin, line);
		if (!cin.eof() && !line.empty()) {
			istringstream iss(line);
			int vi, vj, l;
			iss >> vi >> vj >> l;
			if (vi > nr_villages || vj > nr_villages) {
				int i = max(vi, vj);
				for (int j = nr_villages + 1; j <= i; j++)
					roads[j].clear();
				nr_villages = i;
			}
			roads[vi].push_back(make_pair(vj, l));
			roads[vj].push_back(make_pair(vi, l));
		}
		else if (nr_villages) { // end of a set of input
			int diameter = 0;
			// calculate the diameter (or longest path) of a tree, using depth-first search
			dfs(1, 0, diameter);
			cout << diameter << endl;
			nr_villages = 0;
		}
		else if (!cin.eof()) // no input lines
			cout << 0 << endl;
	} while (!cin.eof());
	return 0;
}

