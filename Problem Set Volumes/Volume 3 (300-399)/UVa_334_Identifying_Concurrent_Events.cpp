
/*
	UVa 334 - Identifying Concurrent Events

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_334_Identifying_Concurrent_Events.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n = 0, N, NC, NM;
		cin >> NC;
		if (!NC)
			break;
		vector<string> names;
		map<string, int> name_indices;
		set< pair<int, int> > edges;
		while (NC--) {
			cin >> N;
			for (int i = 0; i < N; i++) {
				string s;
				cin >> s;
				names.push_back(s);
				name_indices.insert(make_pair(s, n));
				if (i)
					edges.insert(make_pair(n - 1, n));
				n++;
			}
		}
		cin >> NM;
		while (NM--) {
			string s, r;
			cin >> s >> r;
			edges.insert(make_pair(name_indices[s], name_indices[r]));
		}
		vector< vector<bool> > matrix(n, vector<bool>(n, false));
		for (set< pair<int, int> >::const_iterator ei = edges.begin(), ee = edges.end();
			ei != ee; ++ei)
			matrix[ei->first][ei->second] = true;
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cout << matrix[i][j] << ((j < n - 1) ? ' ' : '\n');
#endif
		// apply Warshall's Transitive Closure algorithm
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					matrix[i][j] = matrix[i][j] || matrix[i][k] && matrix[k][j];
		int nr_events = n * (n - 1) / 2;
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				if (matrix[i][j] || matrix[j][i])
					nr_events--;

		cout << "Case " << case_nr << ", ";
		if (nr_events) {
			cout << nr_events << " concurrent events:\n";
			if (nr_events > 2)
				nr_events = 2;
			for (int i = 0; i < n - 1 && nr_events; i++)
				for (int j = i + 1; j < n && nr_events; j++)
					if (!matrix[i][j] && !matrix[j][i]) {
						nr_events--;
						cout << '(' << names[i] << ',' << names[j] << ") ";
					}
			cout << endl;
		}
		else
			cout << "no concurrent events.\n";

	}
	return 0;
}

