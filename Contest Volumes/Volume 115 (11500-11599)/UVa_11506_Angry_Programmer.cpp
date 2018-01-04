
/*
	UVa 11506 - Angry Programmer

	To build using Visucal Studio 2012:
		cl -EHsc UVa_11506_Angry_Programmer.cpp
*/

/*
The max-flow min-cut theorem states that in a flow network, the maximum amount of flow 
passing from the source to the sink is equal to the minimum capacity that, when removed 
in a specific way from the network, causes the situation that no flow can pass from 
the source to the sink.
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

void add_edge(int i, int j, int c, vector< vector<edge> >& graph)
{
	graph[i].push_back(edge(j, c, c));
	graph[j].push_back(edge(i, c, 0));
}

int main()
{
	const int m_max = 50, c_max = m_max * 100000;
	while (true) {
		int m, w;
		cin >> m >> w;
		if (!m && !w)
			break;
		int nr_vertices = 2 * m;
		vector< vector<edge> > graph(nr_vertices);
		// even vertices are for incoming edges, and odd vertices are for outgoing edges.
		// append the edges between each pair of source / sink vertices
		add_edge(0, 1, c_max, graph);
		add_edge(1, 0, c_max, graph);
		add_edge(2 * (m - 1), 2 * (m - 1) + 1, c_max, graph);
		add_edge(2 * (m - 1) + 1, 2 * (m - 1), c_max, graph);
		for (int i = 0; i < m - 2; i++) { // append the edges between each pair of machine vertices
			int j, c;
			cin >> j >> c;
			j--;
			add_edge(2 * j, 2 * j + 1, c, graph);
			add_edge(2 * j + 1, 2 * j, c, graph);
		}
		while (w--) { // append the edges between the machine vertices
			int i, j, c;
			cin >> i >> j >> c;
			i--; j--;
			add_edge(2 * i + 1, 2 * j, c, graph);
			add_edge(2 * j + 1, 2 * i, c, graph);
		}
		netflow(graph, 0, 2 * (m - 1) + 1);
		cout << total_flow(graph, 1) << endl;
	}
	return 0;
}

