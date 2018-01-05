
/*
	UVa 11080 - Place the Guards

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11080_Place_the_Guards.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bfs(int n, int s, const vector< vector<int> >& edges, vector<int>& colors)
// see if a bipartite graph is possible
{
	int cls[2] = {1, 0};
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
				cls[colors[v]]++;
				q.push(v);
			}
			else if (colors[v] == colors[u]) // a cycle found
				return -1;
		}
	}
	if (cls[1])
		return ((cls[0] < cls[1]) ? cls[0] : cls[1]);
	else
		return cls[0];
}

int main()
{
	int T;
	cin >> T;
	while (T--) {
		int v, e;
		cin >> v >> e;
		vector< vector<int> > edges(v);
		while (e--) {
			int f, t;
			cin >> f >> t;
			edges[f].push_back(t);
			edges[t].push_back(f);
		}
		vector<int> colors(v, -1);
		int nr_guards = 0;
		for (int i = 0; i < v; i++)
			if (colors[i] == -1) {
				int j = bfs(v, i, edges, colors);
				if (j != -1)
					nr_guards += j;
				else {
					nr_guards = -1;
					break;
				}
			}
		cout << nr_guards << endl;
	}
	return 0;
}


