
/*
	UVa 11518 - Dominos 2

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11518_Dominos_2.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bfs(int n, int z, const vector< vector<int> >& edges, vector<bool>& visited)
{
	int nr_visited = 0;
	queue<int> q;
	visited[z] = true;
	q.push(z);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		nr_visited++;
		const vector<int>& e = edges[i];
		for (int j = 0; j < e.size(); j++) {
			int k = e[j];
			if (!visited[k]) {
				visited[k] = true;
				q.push(k);
			}
		}
	}
	return nr_visited;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m, l;
		cin >> n >> m >> l;
		vector< vector<int> > edges(n + 1, vector<int>());
		for (int i = 0; i < m; i++) {
			int x, y;
			cin >> x >> y;
			edges[x].push_back(y);
		}
		int nr_dominos = 0;
		vector<bool> visited(n + 1, false);
		for (int i = 0; i < l; i++) {
			int z;
			cin >> z;
			if (!visited[z])
				nr_dominos += bfs(n, z, edges, visited);
		}
		cout << nr_dominos << endl;
	}
	return 0;
}

