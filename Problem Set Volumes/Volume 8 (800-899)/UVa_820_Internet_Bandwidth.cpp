
/*
	UVa 820 - Internet Bandwidth

	To build using Visucal Studio 2008:
		cl -EHsc UVa_820_Internet_Bandwidth.cpp
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

int main(int /* argc */, char** /* argv */)
{
	for (int network_nr = 1; ; network_nr++) {
		int nr_vertices;
		cin >> nr_vertices;
		if (!nr_vertices)
			break;
		int source, sink, nr_connections;
		cin >> source >> sink >> nr_connections;
		source--; sink--;
		vector< vector<int> > bandwidths(nr_vertices, vector<int>(nr_vertices, 0));
		for (int i = 0; i < nr_connections; i++) {
			int j, k, b;
			cin >> j >> k >> b;
			j--; k--;
			bandwidths[j][k] += b; bandwidths[k][j] += b;
		}
		vector< vector<edge> > graph(nr_vertices);
		for (int i = 0; i < nr_vertices; i++)
			for (int j = 0; j < nr_vertices; j++) {
				int b = bandwidths[i][j];
				graph[i].push_back(edge(j, b, b));
			}
		netflow(graph, source, sink);
		cout << "Network " << network_nr << endl;
		cout << "The bandwidth is " << total_flow(graph, source) << ".\n\n";
	}
	return 0;
}

