
/*
	UVa 11902 - Dominator

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11902_Dominator.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void dfs(int i, int excluded, const vector< vector<int> >& edges, vector<bool>& visited)
{
	if (i != excluded) {
		visited[i] = true;
		const vector<int>& es = edges[i];
		for (size_t j = 0, k = es.size(); j < k; j++)
			if (!visited[es[j]])
				dfs(es[j], excluded, edges, visited);
	}
}

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n;
		cin >> n;
		vector< vector<int> > edges(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				int k;
				cin >> k;
				if (k)
					edges[i].push_back(j);
			}
		vector<bool> visited_from_start(n, false);
		dfs(0, -1, edges, visited_from_start);
		vector< vector<bool> > relationships(n, vector<bool>(n, false));
		for (int i = 0; i < n; i++)
			if (visited_from_start[i]) {
				vector<bool> visited(n, false);
				dfs(0, i, edges, visited);
				for (int j = 0; j < n; j++)
					if (visited_from_start[j] && !visited[j])
						relationships[i][j] = true;
			}
		cout << "Case " << case_nr << ":\n";
		string separator = '+' + string(2 * n - 1, '-') + "+\n";
		cout << separator;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << '|' << ((relationships[i][j]) ? 'Y' : 'N');
			cout << "|\n" << separator;
		}
	}
	return 0;
}

