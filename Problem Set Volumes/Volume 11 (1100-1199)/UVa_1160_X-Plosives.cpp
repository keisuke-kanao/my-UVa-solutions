
/*
	UVa 1160 - X-Plosives

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1160_X-Plosives.cpp
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

const int n_max = 100000;
vector<int> edges[n_max + 1];
bool visited[n_max + 1];

int bfs(int s, map<int, bool>& visited)
{
	int nr = 0;
	queue<int> q;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		const vector<int>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i];
			if (!visited[v]) {
				nr++;
				visited[v] = true;
				q.push(v);
			}
		}
	}
	return nr;
}

int main()
{
	int u, v;
	while (cin >> u) {
		for (int i = 0; i <= n_max; i++)
			edges[i].clear();
		map<int, bool> visited;
		cin >> v;
		edges[u].push_back(v);
		edges[v].push_back(u);
		visited[u] = visited[v] = false;
		int n = 1;
		while (true) {
			cin >> u;
			if (u == -1)
				break;
			cin >> v;
			edges[u].push_back(v);
			edges[v].push_back(u);
			visited[u] = visited[v] = false;
			n++;
		}
		int nr = 0;
		for (map<int, bool>::iterator i = visited.begin(), e = visited.end(); i != e; ++i)
			if (!i->second)
				nr += bfs(i->first, visited);
		cout << n - nr << endl;
	}
	return 0;
}

