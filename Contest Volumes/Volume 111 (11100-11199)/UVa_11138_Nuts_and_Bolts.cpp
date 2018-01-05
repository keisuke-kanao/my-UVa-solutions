
/*
	UVa 11138 - Nuts and Bolts

	To build using Visucal Studio 2012:
		cl -EHsc UVa_11138_Nuts_and_Bolts.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
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
	int nr_cases;
	cin >> nr_cases;
	for (int case_nr = 1; case_nr <= nr_cases; case_nr++) {
		int nr_bolts, nr_nuts;
		cin >> nr_bolts >> nr_nuts;
		int nr_vertices = nr_bolts + nr_nuts + 2;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0 - (nr_bolts - 1): bolts vertices, nr_bolts - (nr_bolts + nr_nuts - 1): nuts vertices,
		//	(nr_bolts + nr_nuts): source vertex, (nr_bolts + nr_nuts + 1): sink vertex
		int source = nr_bolts + nr_nuts, sink = nr_bolts + nr_nuts + 1;
		for (int i = 0; i < nr_bolts; i++) {
			// append the edges between the source and bolts vertices
			graph[source].push_back(edge(i, 1, 1));
			graph[i].push_back(edge(source, 1, 0));
			for (int j = 0; j < nr_nuts; j++) {
				int k;
				cin >> k;
				// append the edges between bolts vertices and nuts vertices
				if (k) {
					graph[i].push_back(edge(nr_bolts + j, 1, 1));
					graph[nr_bolts + j].push_back(edge(i, 1, 0));
				}
			}
		}
		for (int i = nr_bolts; i < nr_bolts + nr_nuts; i++) {
			// append the edges between nuts vertices and the sink
			graph[i].push_back(edge(sink, 1, 1));
			graph[sink].push_back(edge(i, 1, 0));
		}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		cout << "Case " << case_nr <<
			": a maximum of " << total_flow(graph, source) << " nuts and bolts can be fitted together\n";
	}
	return 0;
}

