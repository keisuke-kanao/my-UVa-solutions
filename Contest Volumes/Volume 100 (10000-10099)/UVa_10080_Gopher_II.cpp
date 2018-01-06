
/*
	UVa 10080 - Gopher II

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10080_Gopher_II.cpp

	from Waterloo local contest - 17 January 2001
		(http://acm.student.cs.uwaterloo.ca/~acm00/010127/data/)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

const int nr_gophers_max = 100, nr_holes_max = 100;

pair<double, double> gophers[nr_gophers_max], holes[nr_holes_max];

double euclidean_distance(const pair<double, double>& p, const pair<double, double>& q)
{
	double dx = p.first - q.first, dy = p.second - q.second;
	return sqrt(dx * dx + dy * dy);
}

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
	int nr_gophers, nr_holes;
	double seconds, velocity;
	while (cin >> nr_gophers >> nr_holes >> seconds >> velocity) {
		for (int i = 0; i < nr_gophers; i++)
			cin >> gophers[i].first >> gophers[i].second;
		for (int i = 0; i < nr_holes; i++)
			cin >> holes[i].first >> holes[i].second;
		int nr_vertices = nr_gophers + nr_holes + 2;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0 - (nr_gophers - 1): gopher vertices, nr_gophers - (nr_gophers + nr_holes - 1): hole vertices,
		//	(nr_gophers + nr_holes): source vertex, (nr_gophers + nr_holes + 1): sink vertex
		int source = nr_gophers + nr_holes, sink = nr_gophers + nr_holes + 1;
		double d = velocity * seconds;
		for (int i = 0; i < nr_gophers; i++) {
			// append the edges between the source and gopher vertices
			graph[source].push_back(edge(i, 1, 1));
			graph[i].push_back(edge(source, 1, 0));
			for (int j = 0; j < nr_holes; j++)
				if (euclidean_distance(gophers[i], holes[j]) <= d) {
					// append the edges between gopher vertices and hole vertices
					// if a gopher can reach the hole in the specified time
					graph[i].push_back(edge(nr_gophers + j, 1, 1));
					graph[nr_gophers + j].push_back(edge(i, 1, 0));
				}
		}
		for (int i = nr_gophers; i < nr_gophers + nr_holes; i++) {
			// append the edges between hole vertices and the sink
			graph[i].push_back(edge(sink, 1, 1));
			graph[sink].push_back(edge(i, 1, 0));
		}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		cout << nr_gophers - total_flow(graph, source) << endl;
	}
	return 0;
}

