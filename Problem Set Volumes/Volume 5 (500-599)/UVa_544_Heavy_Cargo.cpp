
/*
	UVa Problem 544 Heavy Cargo

	To build using Visucal Studio 2008:
		cl -EHsc UVa_544_Heavy_Cargo.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int get_city_index(const string& name, map<string, int>& cities, bool assign_if_not_found)
{
	map<string, int>::const_iterator i = cities.find(name);
	int index = -1;
	if (i == cities.end()) { // not registered yet
		if (assign_if_not_found) {
			index = cities.size(); // assign an index
			cities.insert(make_pair(name, index));
		}
	}
	else
		index = i->second;
	return index;
}

int main(int /* argc */, char** /* argv */)
{
	for (int scenario = 1; ; scenario++) {
		int n /* number of cities */, r /* number of road segments */;
		cin >> n >> r;
		if (!n && !r)
			break;
		vector< vector<int> > matrix(n, vector<int>(n, -1));
		for (int i = 0; i < n; i++)
			matrix[i][i] = 0;
		map<string, int> cities; // key is a city's name, value is its index to the adjacent matrix
		for (int i = 0; i < r; i++) {
			string c1, c2;
			int w;
			cin >> c1 >> c2 >> w;
			int id1 = get_city_index(c1, cities, true), id2 = get_city_index(c2, cities, true);
			matrix[id1][id2] = matrix[id2][id1] = w;
		}
		string sc, dc;
		cin >> sc >> dc;
		int sid = get_city_index(sc, cities, false), did = get_city_index(dc, cities, false);
		int load = 0;
		if (sid != -1 && did != -1) {
			// the maximin Floyd-Warshall algorithm
			for (int k = 0; k < n; k++)
				for (int i = 0; i < n; i++) {
					if (matrix[i][k] != -1)
						for (int j = 0; j < n; j++)
							if (matrix[k][j] != -1)
								matrix[i][j] = max(matrix[i][j], min(matrix[i][k], matrix[k][j]));
				}
			load = matrix[sid][did];
		}
		cout << "Scenario #" << scenario << endl;
		cout << load << " tons\n\n";
	}
	return 0;
}

