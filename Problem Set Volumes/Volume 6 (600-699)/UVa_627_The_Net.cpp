
/*
	UVa 627 - The Net

	To build using Visual Studio 2008:
		cl -EHsc UVa_627_The_Net.cpp

	This problem is similar to 762 - We Ship Cheap.
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

bool bfs(int source, int destination, const vector< vector<int> >& edges, vector<int>& parents)
{
	vector<bool> visited(edges.size(), false);
	queue<int> q;
	visited[source] = true;
	q.push(source);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		if (i == destination)
			return true;
		const vector<int>& e = edges[i];
		for (int j = 0; j < e.size(); j++) {
			int k = e[j];
			if (!visited[k]) {
				visited[k] = true;
				parents[k] = i;
				q.push(k);
			}
		}
	}
	return false;
}

void print_routes(int i, const vector<int>& parents)
{
	int p = parents[i];
	if (p != -1) {
		print_routes(p, parents);
		cout << ' ';
	}
	cout << i;
}

int main()
{
	int n;
	while (cin >> n) {
		vector< vector<int> > edges(n + 1);
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			char* p;
			int u = strtol(s.c_str(), &p, 10);
			for (p++; ; p++) {
				char* q;
				int v = strtol(p, &q, 10);
				edges[u].push_back(v);
				p = q;
				if (!*p)
					break;
			}
		}
		int m;
		cin >> m;
		cout << "-----\n";
		while (m--) {
			int u, v;
			cin >> u >> v;
			vector<int> parents(edges.size(), -1);
			if (bfs(u, v, edges, parents)) {
				print_routes(v, parents);
				cout << endl;
			}
			else
				cout << "connection impossible\n";
		}
	}
	return 0;
}

