
/*
	UVa 12376 - As Long as I Learn, I Live

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12376_As_Long_as_I_Learn_I_Live.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

int dfs(int u, const vector< vector<int> >& edges, const vector<int>& units, int& gained)
{
	int v = -1, g = 0;
	const vector<int>& es = edges[u];
	for (size_t i = 0, e = es.size(); i < e; i++)
		if (units[es[i]] > g) {
			v = es[i]; g = units[v];
		}
	if (v != -1) {
		gained += g;
		return dfs(v, edges, units, gained);
	}
	else
		return u;
}

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int n, m;
		cin >> n >> m;
		vector<int> units(n);
		for (int i = 0; i < n; i++)
			cin >> units[i];
		vector< vector<int> > edges(n);
		while (m--) {
			int u, v;
			cin >> u >> v;
			edges[u].push_back(v);
		}
		int gained = 0;
		int v = dfs(0, edges, units, gained);
		cout << "Case " << t << ": " << gained << ' ' << v << endl;
	}
	return 0;
}

