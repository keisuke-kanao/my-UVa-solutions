
/*
	UVa 10806 - Dijkstra, Dijkstra.

	To build using Visucal Studio 2010:
		cl -EHsc UVa_10806_Dijkstra_Dijkstra.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

struct edge {
	int v_;
	size_t vi_;
	int capacity_, cost_;
	int flow_;

	edge(int v, size_t vi, int capacity, int cost) : v_(v), vi_(vi), capacity_(capacity), cost_(cost), flow_(0) {}
};

void shortest_path(int n, int start, const vector< vector<edge> >& edges,
	vector< pair<int, size_t> >& parents, vector<int>& distances)
{
	queue<int> q;
	vector<bool> visited(n, false);
	for (int i = 0; i < n; i++) {
		parents[i] = make_pair(-1, 0);
		distances[i] = numeric_limits<int>::max();
	}
	distances[start] = 0;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		visited[u] = false;
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i].v_;
			if (es[i].flow_ < es[i].capacity_ && distances[u] + es[i].cost_ < distances[v]) {
				distances[v] = distances[u] + es[i].cost_;
				parents[v] = make_pair(u, i);
				if (!visited[v]) {
					visited[v] = true;
					q.push(v);
				}
			}
		}
	}
}

int minimum_cost_maximum_flow(int n, vector< vector<edge> >& edges)
{
	int flow = 0, cost = 0;
	vector< pair<int, size_t> > parents(n);
	vector<int> distances(n);
	while (true) {
		shortest_path(n, 0, edges, parents, distances);
		if (distances[n - 1] == numeric_limits<int>::max())
			break;
		int min_flow = numeric_limits<int>::max();
		for (pair<int, size_t> p = parents[n - 1]; p.first != -1; p = parents[p.first]) {
			edge& e = edges[p.first][p.second];
			min_flow = min(min_flow, e.capacity_ - e.flow_);
		}
		for (pair<int, size_t> p = parents[n - 1]; p.first != -1; p = parents[p.first]) {
			edges[p.first][p.second].flow_ += min_flow;
			edges[edges[p.first][p.second].v_][edges[p.first][p.second].vi_].flow_ -= min_flow;
		}
		flow += min_flow;
		cost += distances[n - 1] * min_flow;
#ifdef DEBUG
		cout << flow << ' ' << cost << endl;
#endif
	}
	return (flow == 2) ? cost : -1;
}

int main()
{
	while (true) {
		int n, m;
		cin >> n;
		if (!n)
			break;
		vector< vector<edge> > edges(n + 2); // edges[i] is the vector of edges from the i-th vertex
		cin >> m;
		while (m--) {
			int u, v, w;
			cin >> u >> v >> w;
			size_t ui = edges[u].size(), vi = edges[v].size();
			edges[u].push_back(edge(v, vi, 1, w));
			edges[v].push_back(edge(u, ui, 0, -w));
			edges[v].push_back(edge(u, ui + 1, 1, w));
			edges[u].push_back(edge(v, vi + 1, 0, -w));
		}
		edges[0].push_back(edge(1, edges[1].size(), 2, 0));
		edges[1].push_back(edge(0, 0, 0, 0));
		edges[n].push_back(edge(n + 1, 0, 2, 0));
		edges[n + 1].push_back(edge(n, edges[n].size(), 0, 0));
		int min_cost = minimum_cost_maximum_flow(n + 2, edges);
		if (min_cost == -1)
			cout << "Back to jail\n";
		else
			cout << min_cost << endl;
	}
	return 0;
}

