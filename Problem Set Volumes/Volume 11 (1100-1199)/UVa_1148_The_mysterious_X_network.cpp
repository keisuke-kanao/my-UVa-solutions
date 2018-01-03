
/*
	UVa 1148 - The mysterious X network

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1148_The_mysterious_X_network.cpp
*/

#include <vector>
#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

int bfs(int n, int s, int e, const vector< vector<int> >& adjacency_list)
{
	vector<bool> visited(n, false);
	queue< pair<int, int> > q;
	visited[s] = true;
	q.push(make_pair(s, -1));
	while (!q.empty()) {
		pair<int, int> u = q.front(); q.pop();
		if (u.first == e)
			return u.second;
		const vector<int>& al = adjacency_list[u.first];
		for (size_t i = 0, e = al.size(); i < e; i++) {
			int v = al[i];
			if (!visited[v]) {
				visited[v] = true;
				q.push(make_pair(v, u.second + 1));
			}
		}
	}
	return -1;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		vector< vector<int> > adjacency_list(n);
		for (int i = 0; i < n; i++) {
			int c, nc;
			scanf("%d %d", &c, &nc);
			vector<int>& al = adjacency_list[c];
			while (nc--) {
				int j;
				scanf("%d", &j);
				al.push_back(j);
			}
		}
		int c1, c2;
		scanf("%d %d", &c1, &c2);
		printf("%d %d %d\n", c1, c2, bfs(n, c1, c2, adjacency_list));
		if (t)
			putchar('\n');
	}
	return 0;
}

