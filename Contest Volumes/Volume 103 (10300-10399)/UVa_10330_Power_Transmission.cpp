
/*
	UVa 10330 - Power Transmission

	To build using Visucal Studio 2012:
		cl -EHsc UVa_10330_Power_Transmission.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

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
	int n;
	while (cin >> n) {
		int nr_vertices = 2 * n + 2;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		// 0 - (2 * n - 1): regulator vertices, 2 * n: source vertex, 2 * n + 1: sink vertex
		// Note that each regulators are treated as a pair of vertices.
		int source = 2 * n, sink = 2 * n + 1;
		vector<int> rcs(n); // regulator capacities
		for (int i = 0; i < n; i++) { // append the edges between each pair of regulator vertices
			cin >> rcs[i];
			graph[2 * i].push_back(edge(2 * i + 1, rcs[i], rcs[i]));
			graph[2 * i + 1].push_back(edge(2 * i, rcs[i], 0));
		}
		int m;
		cin >> m;
		while (m--) { // append the edges between regulators
			int i, j, c;
			cin >> i >> j >> c;
			i--; j--;
			graph[2 * i + 1].push_back(edge(2 * j, c, c));
			graph[2 * j].push_back(edge(2 * i + 1, c , 0));
		}
		int b, d;
		cin >> b >> d;
		while (b--) { // append the edges from the source to regulators
			int i;
			cin >> i;
			i--;
			graph[source].push_back(edge(2 * i, rcs[i], rcs[i]));
			graph[2 * i].push_back(edge(source, rcs[i], 0));
		}
		while (d--) { // append the edges from regulators to the sink
			int i;
			cin >> i;
			i--;
			graph[2 * i + 1].push_back(edge(sink, rcs[i], rcs[i]));
			graph[sink].push_back(edge(2 * i + 1, rcs[i], 0));
		}
		netflow(graph, source, sink);
		cout << total_flow(graph, source) << endl;
	}
	return 0;
}

