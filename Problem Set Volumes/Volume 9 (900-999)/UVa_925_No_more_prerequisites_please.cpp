
/*
	UVa 925 - No more prerequisites, please!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_925_No_more_prerequisites_please.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
	int C;
	cin >> C;
	while (C--) {
		int i, j, k, n;
		cin >> n;
		vector<string> names(n);
		for (i = 0; i < n; i++)
			cin >> names[i];
		sort(names.begin(), names.end());
		map<string, int> name_indices;
		for (int i = 0; i < n; i++)
			name_indices[names[i]] = i;
		vector< vector<int> > adjacency_list(n);
		vector< vector<bool> > adjacency_matrix(n, vector<bool>(n, false));;
		cin >> j;
		while (j--) {
			string cs, ps;
			int d, u, v;
			cin >> cs >> d;
			u = name_indices[cs];
			for (i = 0; i < d; i++) {
				cin >> ps;
				v = name_indices[ps];
                adjacency_matrix[u][v] = true;
                adjacency_list[u].push_back(v);
			}
		}
		// apply Warshall's Transitive Closure algorithm (in reverse directions)
        for (k = 0; k < n; k++)
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					adjacency_matrix[i][j] = adjacency_matrix[i][j] || adjacency_matrix[i][k] && adjacency_matrix[k][j];

		for (int i = 0; i < n; i++) {
			const vector<int>& al = adjacency_list[i];
			vector<int> prerequisites;
			size_t ale = al.size();
			for (size_t ui = 0; ui < ale; ui++) {
				int u = al[ui];
				bool prerequisite = true;
				for (size_t vi = 0; vi < ale && prerequisite; vi++)
					if (ui != vi) {
						int v = al[vi];
						if (adjacency_matrix[v][u])
							prerequisite = false;
					}
				if (prerequisite)
					prerequisites.push_back(u);
			}
			if (!prerequisites.empty()) {
				sort(prerequisites.begin(), prerequisites.end());
				cout << names[i] << ' ' << prerequisites.size();
				for (size_t pi = 0, pe = prerequisites.size(); pi != pe; ++pi)
					cout << ' ' << names[prerequisites[pi]];
				cout << endl;
			}
		}
	}
	return 0;
}

