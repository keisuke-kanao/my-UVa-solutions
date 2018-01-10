
/*
	UVa 10305 - Ordering Tasks

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10305_Ordering_Tasks.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void topologica_sort(int n, vector<int>& in_degrees, const vector< vector<int> >& graph, vector<int>& orders)
{
	queue<int> q;
	for (int i = 0; i < n; i++)
		if (!in_degrees[i])
			q.push(i);
	int oi = 0;
	while (!q.empty()) {
		int i = q.front(); q.pop();
		orders[oi++] = i;
		const vector<int>& g = graph[i];
		for (size_t j = 0, k = g.size(); j < k; j++)
			if (!--in_degrees[g[j]])
				q.push(g[j]);
	}
}

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		vector<int> in_degrees(n, 0);
		vector< vector<int> > graph(n, vector<int>());
		for (int i = 0; i < m; i++) {
			int j, k;
			cin >> j >> k;
			graph[--j].push_back(--k);
			in_degrees[k]++;
		}
		vector<int> orders(n);
		topologica_sort(n, in_degrees, graph, orders);
		for (size_t i = 0, e = orders.size(); i < e; i++)
			cout << orders[i] + 1 << ((i == e - 1) ? '\n' : ' ');
	}
	return 0;
}

