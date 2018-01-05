
/*
	UVa 11396 - Claw Decomposition

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11396_Claw_Decomposition.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bfs(int s, const vector< vector<int> >& edges, vector<int>& colors)
// see if a bipartite graph is possible
{
	queue<int> q;
	colors[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		const vector<int>& e = edges[u];
		for (size_t i = 0; i < e.size(); i++) {
			int v = e[i];
			if (colors[v] == -1) { // not visited yet
				colors[v] = 1 - colors[u];
				q.push(v);
			}
			else if (colors[v] == colors[u]) // a cycle found
				return false;
		}
	}
	return true;
}

int main()
{
	while (true) {
		int v;
		cin >> v;
		if (!v)
			break;
		vector< vector<int> > edges(v + 1);
		while (true) {
			int a, b;
			cin >> a >> b;
			if (!a && !b)
				break;
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		bool claws = true;
		vector<int> colors(v + 1, -1);
		int nr_guards = 0;
		for (int i = 1; i <= v; i++)
			if (colors[i] == -1) {
				if (!bfs(i, edges, colors)) {
					claws = false;
					break;
				}
			}
		cout << ((claws) ? "YES\n" : "NO\n");
	}
	return 0;
}

