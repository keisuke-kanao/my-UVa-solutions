
/*
	UVa 11159 - Factors and Multiples

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11159_Factors_and_Multiples.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
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

const int n_max = 100, m_max = 100;
int n_integers[n_max], m_integers[m_max];

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int n, m;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> n_integers[i];
		cin >> m;
		for (int i = 0; i < m; i++)
			cin >> m_integers[i];
		int nr_vertices = n + m + 2;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0 - (n - 1): n_integers vertices, n - (n + m - 1): m_integers vertices,
		//	(n + m): source vertex, (n + m + 1): sink vertex
		int source = n + m, sink = n + m + 1;
		for (int i = 0; i < n; i++) {
			// append the edges between the source and n_integers vertices
			graph[source].push_back(edge(i, 1, 1));
			graph[i].push_back(edge(source, 1, 0));
			// append the edges between n_integers and m_integers
			for (int j = 0; j < m; j++)
				if (n_integers[i] && !(m_integers[j] % n_integers[i]) ||
					!n_integers[i] && !m_integers[j]) {
					graph[i].push_back(edge(n + j, 1, 1));
					graph[n + j].push_back(edge(i, 1, 0));
				}
		}
		for (int i = n; i < n + m; i++) {
			// append the edges between m_integers vertices and the sink
			graph[i].push_back(edge(sink, 1, 1));
			graph[sink].push_back(edge(i, 1, 0));
		}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		cout << "Case " << t << ": " << total_flow(graph, source) << endl;
	}
	return 0;
}

