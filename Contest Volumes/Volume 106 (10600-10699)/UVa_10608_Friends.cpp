
/*
	UVa 10608 - Friends

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10608_Friends.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int n_max = 30000;
vector< vector<int> > adjacency_list(n_max + 1);
bool visited[n_max + 1];

int bfs(int v)
{
	int nr_vertices = 0;
	queue<int> q;
	visited[v] = true;
	q.push(v);
	nr_vertices++;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		const vector<int>& l = adjacency_list[u];
		for (size_t i = 0, e = l.size(); i < e; i++) {
			v = l[i];
			if (!visited[v]) {
				visited[v] = true;
				q.push(v);
				nr_vertices++;
			}
		}
	}
	return nr_vertices;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			adjacency_list[i].clear();
			visited[i] = false;
		}
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			adjacency_list[u].push_back(v);
			adjacency_list[v].push_back(u);
		}
		int max_nr_vertices = 0;
		for (int i = 1; i <= n; i++)
			if (!visited[i]) {
				int nr_vertices = bfs(i);
				if (nr_vertices > max_nr_vertices)
					max_nr_vertices = nr_vertices;
			}
		cout << max_nr_vertices << endl;
	}
	return 0;
}

