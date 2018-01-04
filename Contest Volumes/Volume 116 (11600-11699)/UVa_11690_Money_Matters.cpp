
/*
	UVa 11690 - Money Matters

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11690_Money_Matters.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int n_max = 10000;

vector<int> edges[n_max];
bool visited[n_max];
int owes[n_max];

int bfs(int v)
{
	queue<int> q;
	int owe = owes[v];
	visited[v] = true;
	q.push(v);
	while (!q.empty()) {
		const vector<int>& e = edges[q.front()];
		q.pop();
		for (size_t i = 0, j = e.size(); i < j; i++) {
			v = e[i];
			if (!visited[v]) {
				owe += owes[v];
				visited[v] = true;
				q.push(v);
			}
		}
	}
	return owe;
}

int main()
{
	int N;
	cin >> N;
	while (N--) {
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			edges[i].clear();
			visited[i] = false;
			cin >> owes[i];
		}
		while (m--) {
			int x, y;
			cin >> x >> y;
			edges[x].push_back(y);
			edges[y].push_back(x);
		}
		bool possible = true;
		for (int i = 0; i < n && possible; i++)
			if (!visited[i] && bfs(i))
				possible = false;
		cout << ((possible) ? "POSSIBLE\n" : "IMPOSSIBLE\n");
	}
	return 0;
}

