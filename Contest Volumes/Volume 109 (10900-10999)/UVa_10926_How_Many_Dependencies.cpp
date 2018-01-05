
/*
	UVa 10926 - How Many Dependencies?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10926_How_Many_Dependencies.cpp
*/

#include <iostream>
#include <queue>
using namespace std;

const int n_max = 100;
bool visited[n_max + 1];
bool matrix[n_max + 1][n_max + 1];

int bfs(int v, int n)
{
	for (int i = 1; i <= n; i++)
		visited[i] = false;
	int nr_vertices = 0;
	queue<int> q;
	visited[v] = true;
	q.push(v);
	nr_vertices++;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 1; v <= n; v++) {
			if (matrix[u][v] && !visited[v]) {
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
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				matrix[i][j] = false;
		for (int i = 1; i <= n; i++) {
			int t;
			cin >> t;
			for (int j = 0; j < t; j++) {
				int k;
				cin >> k;
				matrix[i][k] = true;
			}
		}
		int max_vertices = 0, max_v = -1;
		for (int v = 1; v <= n; v++) {
			int vertices = bfs(v, n);
			if (vertices > max_vertices) {
				max_vertices = vertices; max_v = v;
			}
		}
		cout << max_v << endl;
	}
	return 0;
}

