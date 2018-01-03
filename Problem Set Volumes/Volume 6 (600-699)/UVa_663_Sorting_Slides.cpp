
/*
	UVa 663 - Sorting Slides

	To build using Visucal Studio 2012:
		cl -EHsc UVa_663_Sorting_Slides.cpp
*/

#include <vector>
#include <queue>
#include <utility>
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

struct slide {
	int x_min_, x_max_, y_min_, y_max_;
};

struct number {
	int x_, y_;
};

void add_edge(int i, int j, vector< vector<edge> >& graph) // add an edge from i to j
{
	graph[i].push_back(edge(j, 1, 1));
	graph[j].push_back(edge(i, 1, 0));
}

bool number_in_slide(const slide& s, const number& n)
{
	return n.x_ > s.x_min_ && n.x_ < s.x_max_ && n.y_ > s.y_min_ && n.y_ < s.y_max_;
}

int maximum_bipertite_matching(int n, int esi, int eni, const vector<slide>& slides, const vector<number>& numbers)
{
	int nr_vertices = n * 2 + 2;
	vector< vector<edge> > graph(nr_vertices);
	// indices are:
	//	0 - (n - 1): slide vertices, n - (n * 2 - 1): number vertices,
	//	n * 2: source vertex, (n * 2 + 1): sink vertex
	int source = n * 2, sink = n * 2 + 1;
	for (int i = 0; i < n; i++) // add the edges between slide vertices and number vertices
		if (i != esi) // exclude esi-th slide
			for (int j = 0; j < n; j++)
				if (j != eni && // exclude eni-th number
					number_in_slide(slides[i], numbers[j]))
					add_edge(i, n + j, graph);
	for (int i = 0; i < n; i++) {
		add_edge(source, i, graph); // add an edge from the source vertex to a slide vertex
		add_edge(n + i, sink, graph); // add an edge from a number vertex to sink vertex
	}
	netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
	return total_flow(graph, source);
}

int main()
{
	for (int heap_nr = 1; ; heap_nr++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		vector<slide> slides(n);
		for (int i = 0; i < n; i++)
			scanf("%d %d %d %d", &slides[i].x_min_, &slides[i].x_max_, &slides[i].y_min_, &slides[i].y_max_);
		vector<number> numbers(n);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &numbers[i].x_, &numbers[i].y_);
		vector<int> unique_matchings(n, -1);
		for (int i = 0; i < n; i++) // for each slide
			for (int j = 0; j < n; j++) // for each number
				if (number_in_slide(slides[i], numbers[j]) &&
					maximum_bipertite_matching(n, i, j, slides, numbers) == n - 1) { // perfect matching
					if (unique_matchings[i] == -1)
						unique_matchings[i] = j;
					else { // not unique
						unique_matchings[i] = -1;
						break;
					}
				}
		printf("Heap %d\n", heap_nr);
		bool none = true;
		for (int i = 0; i < n; i++)
			if (unique_matchings[i] != -1) {
				if (none)
					none = false;
				else
					putchar(' ');
				printf("(%c,%d)", 'A' + i, unique_matchings[i] + 1);
			}
		if (none)
			printf("none\n\n");
		else
			printf("\n\n");
	}
	return 0;
}

