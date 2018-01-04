
/*
	UVa 11419 - SAM I AM

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11419_SAM_I_AM.cpp
*/

#include <vector>
#include <queue>
#ifndef __RECURSION__
#include <stack>
#endif
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

void add_edge(int u, int v, vector< vector<edge> >& graph)
{
	graph[u].push_back(edge(v, 1, 1));
	graph[v].push_back(edge(u, 1, 0));
}

#ifdef __RECURSION__
void dfs(int i, vector< vector<edge> >& graph, vector<bool>& visited)
{
	visited[i] = true;
	const vector<edge>& edges = graph[i];
	for (size_t j = 0, e = edges.size(); j < e; j++)
		if (edges[j].residual && !visited[edges[j].v])
			dfs(edges[j].v, graph, visited);
}
#else
void dfs(int i, vector< vector<edge> >& graph, vector<bool>& visited)
{
	stack<int> st;
	visited[i] = true;
	st.push(i);
	while (!st.empty()) {
		i = st.top();
		const vector<edge>& edges = graph[i];
		bool pushed = false;
		for (size_t j = 0, e = edges.size(); j < e; j++) {
			if (edges[j].residual) {
				int k = edges[j].v;
				if (!visited[k]) {
					visited[k] = true;
					st.push(k);
					pushed = true;
				}
			}
			if (pushed)
				break;
		}
		if (!pushed)
			st.pop();
	}
}
#endif

int main()
{
	while (true) {
		int R, C, N;
		scanf("%d %d %d", &R, &C, &N);
		if (!R)
			break;
		int nr_vertices = R + C + 2, source = R + C, sink = R + C + 1;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0 to (R - 1): row vertices, R to (R + C - 1): column vertices,
		// (R + C + N): source vertex, (R + C + N + 1): sink vertex
		for (int i = 0; i < R; i++)
			add_edge(source, i, graph);
		for (int i = 0; i < C; i++)
			add_edge(R + i, sink, graph);
		for (int n = 0; n < N; n++) {
			int r, c;
			scanf("%d %d", &r, &c);
			add_edge(r - 1, R + c - 1, graph);
		}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
#ifdef DEBUG
		for (int i = 0; i < nr_vertices; i++) {
			printf("%d:", i);
			const vector<edge>& edges = graph[i];
			for (size_t j = 0, e = edges.size(); j < e; j++)
				if (edges[j].residual)
					printf(" %d", edges[j].v);
			putchar('\n');
		}
#endif
		// do depth-first seach on the residual graph
		vector<bool> visited(nr_vertices, false);
		dfs(source, graph, visited);
		printf("%d", total_flow(graph, source));
		// prit the not-visited rows and visited columns
		for (int i = 0; i < R; i++)
			if (!visited[i])
				printf(" r%d", i + 1);
		for (int i = 0; i < C; i++)
			if (visited[R + i])
				printf(" c%d", i + 1);
		putchar('\n');
	}
	return 0;
}

