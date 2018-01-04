
/*
	UVa 259 - Software Allocation

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_259_Software_Allocation.cpp
*/

#include <iostream>
#include <string>
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

const int nr_applications = 'Z' - 'A' + 1, nr_computers = 9 - 0 + 1;
const int nr_vertices = nr_applications + nr_computers + 2;
const int source = nr_applications + nr_computers, sink = nr_applications + nr_computers + 1;

void print_allocation(const vector< vector<edge> >& graph)
{
	char ac[nr_computers + 1];
	for (int i = 0; i < nr_computers; i++)
		ac[i] = '_';
	ac[nr_computers] = '\0';
	for (int i = 0; i < nr_applications; i++) {
		const vector<edge>& edges = graph[i];
		for (int j = 0, e = edges.size(); j < e; j++)
			if (edges[j].flow) {
				ac[edges[j].v - nr_applications] = static_cast<char>(i + 'A');
			}
	}
	cout << ac << endl;
}

int main()
{
	string s;
	while (getline(cin, s)) {
		int allocation = 0;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0 - (nr_applications - 1): application vertices, 
		//	nr_applications - (nr_applications + nr_computers - 1): computer vertices,
		//	(nr_applications + nr_computers): source vertex, (nr_applications + nr_computers + 1): sink vertex
		do {
			const char* p = s.c_str();
			int u = *p++ - 'A', d = *p++ - '0';
			allocation += d;
			// append the edges between the source and application vertices
			graph[source].push_back(edge(u, d, d));
			graph[u].push_back(edge(source, d, 0));
			for (p++; *p != ';'; p++) {
				int v = nr_applications + *p - '0';
				// append the edges between the application and the computer vertices
				graph[u].push_back(edge(v, 1, 1));
				graph[v].push_back(edge(u, 1, 0));
			}
		} while (getline(cin, s) && !s.empty());
		for (int i = nr_applications; i < nr_applications + nr_computers; i++) {
			// append the edges between computer vertices and the sink
			graph[i].push_back(edge(sink, 1, 1));
			graph[sink].push_back(edge(i, 1, 0));
		}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		if (total_flow(graph, source) == allocation)
			print_allocation(graph);
		else
			cout << "!\n";
	}
	return 0;
}

