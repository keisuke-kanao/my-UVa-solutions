
/*
	UVa 10480 - Sabotage

	To build using Visucal Studio 2012:
		cl -EHsc UVa_10480_Sabotage.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
using namespace std;

/*
Following are steps to print all edges of minimum cut.
  1) Run Ford-Fulkerson algorithm and consider the final residual graph.
  2) Find the set of vertices that are reachable from source in the residual graph.
  3) All edges which are from a reachable vertex to non-reachable vertex are minimum cut edges. Print all such edges.
*/

struct edge {
	int v; // neighboring vertex
	int capacity; // capacity of edge
	int flow; // flow through edge
	int residual; // residual capacity of edge

	edge(int _v, int _capacity, int _residual) : v(_v), capacity(_capacity), flow(0), residual(_residual) {}
};

struct vertex_state {
	bool discovered;
	int parent;

	vertex_state() : discovered(false), parent(-1) {}
};

void bfs(const vector< vector<edge> >& graph, int start, vector<vertex_state>& states)
{
	queue<int> q;
	states[start].discovered = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < graph[u].size(); i++) {
			const edge& e = graph[u][i];
			if (e.residual > 0 && !states[e.v].discovered) {
				states[e.v].discovered = true;
				states[e.v].parent = u;
				q.push(e.v);
			}
		}
	}
}

edge& find_edge(vector< vector<edge> >& graph, int u, int v)
{
	int i;
	for (i = 0; i < graph[u].size(); i++)
		if (graph[u][i].v == v)
			break;
	return graph[u][i];
}

int path_volume(vector< vector<edge> >& graph, int start, int end, const vector<vertex_state>& states)
{
	if (states[end].parent == -1)
		return 0;
	edge& e = find_edge(graph, states[end].parent, end);
	if (start == states[end].parent)
		return e.residual;
	else
		return min(path_volume(graph, start, states[end].parent, states), e.residual);
}

void augment_path(vector< vector<edge> >& graph, int start, int end, const vector<vertex_state>& states, int volume)
{
	if (start == end)
		return;
	edge& e = find_edge(graph, states[end].parent, end);
	if (e.flow < e.capacity)
		e.flow += volume;
	if (e.residual)
		e.residual -= volume;
	edge& r= find_edge(graph, end, states[end].parent);
	if (r.flow)
		r.flow -= volume;
	if (r.residual < r.capacity)
		r.residual += volume;
	augment_path(graph, start, states[end].parent, states, volume);
}

void netflow(vector< vector<edge> >& graph, int source, int sink)
{
	while (true) {
		vector<vertex_state> states(graph.size());
		bfs(graph, source, states);
		int volume = path_volume(graph, source, sink, states); // calculate the volume of augmenting path
		if (volume > 0)
			augment_path(graph, source, sink, states, volume);
		else
			break;
	}
}

int total_flow(const vector< vector<edge> >& graph, int source)
{
	int flow = 0;
	const vector<edge>& edges = graph[source];
	for (int i = 0, e = edges.size(); i < e; i++)
		flow += edges[i].flow;
	return flow;
}

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m)
			break;
		vector< vector<edge> > graph(n);
		while (m--) {
			int u, v, c;
			cin >> u >> v >> c;
			u--; v--;
			graph[u].push_back(edge(v, c, c));
			graph[v].push_back(edge(u, c, c));
		}
		netflow(graph, 0, 1);
#ifdef DEBUG
		cout << total_flow(graph, 0) << endl;
		for (int i = 0; i < n; i++)
			for (size_t j = 0; j < graph[i].size(); j++)
				cout << i << ' ' <<  graph[i][j].v << ": " <<
					graph[i][j].capacity << ' ' << graph[i][j].flow << ' ' << graph[i][j].residual << endl;
#endif
		vector<vertex_state> states(n);
		bfs(graph, 0, states);
#ifndef ONLINE_JUDGE
		int min_cut = 0;
#endif
		for (int i = 0; i < n; i++)
			if (states[i].discovered) {
				const vector<edge>& es = graph[i];
				for (size_t j = 0, k = es.size(); j < k; j++)
					if (!states[es[j].v].discovered) {
#ifndef ONLINE_JUDGE
						min_cut += es[j].capacity;
#endif
						cout << i + 1 << ' ' << es[j].v + 1 << endl;
					}
			}
#ifndef ONLINE_JUDGE
		assert(total_flow(graph, 0) == min_cut);
#endif
		cout << endl;
	}
	return 0;
}

