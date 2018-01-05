
/*
	UVa 10349 - Antenna Placement

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10349_Antenna_Placement.cpp
*/

#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
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

void add_edge(int u, int v, int c, vector< vector<edge> >& graph)
{
	graph[u].push_back(edge(v, c, c));
	graph[v].push_back(edge(u, c, 0));
}

int main()
{
	int nsc;
	scanf("%d", &nsc);
	while (nsc--) {
		int h, w;
		scanf("%d %d", &h, &w);
		const int h_max = 40, w_max = 10;
		char matrix[h_max][w_max];
		for (int i = 0; i < h; i++)
			scanf("%s", matrix[i]);
		int nr_vertices = h * w + 2, ni = 0;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0: source vertex, 1 - h * w: point of interest/open space vertices,
		// h * w + 1 (or nr_vertices - 1): sink vertex
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++)
				if (matrix[i][j] == '*') {
					ni++;
					if( (i + j) % 2) {
						// append the edges from the source vertex to the open space vertrex
						add_edge(0, i * w + j + 1, 1, graph);
						// append the edges between the open space vertex to the point of interest vertices
						if (i && matrix[i - 1][j] == '*')
							add_edge(i * w + j + 1, (i - 1) * w + j + 1, 1, graph);
						if (i < h - 1 && matrix[i + 1][j] == '*')
							add_edge(i * w + j + 1, (i + 1) * w + j + 1, 1, graph);
						if (j && matrix[i][j - 1] == '*')
							add_edge(i * w + j + 1, i * w + j, 1, graph);
						if (j < w - 1 && matrix[i][j + 1] == '*')
							add_edge(i * w + j + 1, i * w + j + 2, 1, graph);
					}
					else
						add_edge(i * w + j + 1, nr_vertices - 1, 1, graph);
				}
		}
		netflow(graph, 0, nr_vertices - 1); // apply Ford-Fulkerson's augmenting path algorithm
		int max_matching = total_flow(graph, 0);
#ifdef DEBUG
		printf("%d %d\n", ni, max_matching);
#endif
		printf("%d\n", max_matching + ni - max_matching * 2);
	}
	return 0;
}

