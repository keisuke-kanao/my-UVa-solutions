
/*
	UVa 563 - Crimewave

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_563_Crimewave.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cctype>
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
	int p;
	cin >> p;
	while (p--) {
		int s, a, b;
		cin >> s >> a >> b;
		vector< vector<bool> > crossings(s, vector<bool>(a, false));
		for (int i = 0; i < b; i++) {
			int x, y;
			cin >> x >> y;
			crossings[x - 1][y - 1] = true;
		}
		int nr_crossing_vertices = s * a * 2;
		// indices are:
		// 0 - s * a * 2 - 1: crossing vertices (two vertices per crossing),
		// s * a * 2: source vertex, s * a * 2 + 1: sink vertex
		int nr_vertices = nr_crossing_vertices + 2,
			source = nr_crossing_vertices, sink = nr_crossing_vertices + 1;
		vector< vector<edge> > graph(nr_vertices);
		for (int i = 0; i < s; i++)
			for (int j = 0; j < a; j++) {
				int u = (i * a + j) * 2, v;
				// append edges between the two crossing vertices (u for in, (u + 1) for out)
				graph[u].push_back(edge(u + 1, 1, 1));
				graph[u + 1].push_back(edge(u, 1, 0));
				if (crossings[i][j]) {
					// append edges from the source to the banks
					graph[source].push_back(edge(u, 1, 1));
					graph[u].push_back(edge(source, 1, 0));
				}
				else {
					// append adges from adjacent crosssing vertices
					if (i) {
						v = ((i - 1) * a + j) * 2 + 1;
						graph[v].push_back(edge(u, 1, 1));
						graph[u].push_back(edge(v, 1, 0));
					}
					if (i < s - 1) {
						v = ((i + 1) * a + j) * 2 + 1;
						graph[v].push_back(edge(u, 1, 1));
						graph[u].push_back(edge(v, 1, 0));
					}
					if (j) {
						v = (i * a + j - 1) * 2 + 1;
						graph[v].push_back(edge(u, 1, 1));
						graph[u].push_back(edge(v, 1, 0));
					}
					if (j < a - 1) {
						v = (i * a + j + 1) * 2 + 1;
						graph[v].push_back(edge(u, 1, 1));
						graph[u].push_back(edge(v, 1, 0));
					}
				}
				if (!i || i == s - 1 || !j || j == a - 1) {
					// append edges to sink vertex
					graph[u + 1].push_back(edge(sink, 1, 1));
					graph[sink].push_back(edge(u + 1, 1, 0));
				}
				else {
					// append adges to adjacent crosssing vertices
					v = ((i - 1) * a + j) * 2;
					graph[u + 1].push_back(edge(v, 1, 1));
					graph[v].push_back(edge(u + 1, 1, 0));
					v = ((i + 1) * a + j) * 2;
					graph[u + 1].push_back(edge(v, 1, 1));
					graph[v].push_back(edge(u + 1, 1, 0));
					v = (i * a + j - 1) * 2;
					graph[u + 1].push_back(edge(v, 1, 1));
					graph[v].push_back(edge(u + 1, 1, 0));
					v = (i * a + j + 1) * 2;
					graph[u + 1].push_back(edge(v, 1, 1));
					graph[v].push_back(edge(u + 1, 1, 0));
				}
			}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		cout << ((total_flow(graph, source) == b) ? "possible\n" : "not possible\n");
	}
	return 0;
}

