
/*
	UVa 280 - Vertex

	To build using Visual Studio 2008:
		cl -EHsc UVa_280_Vertex.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int bfs(int n, int s, const vector< vector<int> >& edges, vector<bool>& visited)
{
	int nr_visited = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		const vector<int>& e = edges[q.front()];
		q.pop();
		for (size_t i = 0, j = e.size(); i < j; i++) {
			int k = e[i];
			if (!visited[k]) {
				visited[k] = true;
				nr_visited++;
				q.push(k);
			}
		}
	}
	return n - nr_visited;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector< vector<int> > edges(n + 1);
		while (true) {
			int i;
			cin >> i;
			if (!i)
				break;
			while (true) {
				int j;
				cin >> j;
				if (!j)
					break;
				edges[i].push_back(j);
			}
		}
		vector<bool> visited(n + 1);
		int i;
		cin >> i;
		for (int j = 0; j < i; j++) {
			int s;
			cin >> s;
			for (int k = 1; k <= n; k++)
				visited[k] = false;
			int nr_inaccessible = bfs(n, s, edges, visited);
			cout << nr_inaccessible;
			for (int k = 1; k <= n && nr_inaccessible; k++)
				if (!visited[k]) {
					cout << ' ' << k;
					nr_inaccessible--;
				}
			cout << endl;
		}
	}
	return 0;
}

