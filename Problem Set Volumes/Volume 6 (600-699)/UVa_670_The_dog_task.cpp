
/*
	UVa 670 - The dog task

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_670_The_dog_task.cpp
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

struct point {
	int x_, y_;
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = static_cast<double>(a.x_ - b.x_), dy = static_cast<double>(a.y_ - b.y_);
	return sqrt(dx * dx + dy * dy);
}

int main()
{
	int l;
	cin >> l;
	while (l--) {
		int n, m;
		cin >> n >> m;
		vector<point> routes(n), places(m);
		for (int i = 0; i < n; i++)
			cin >> routes[i].x_ >> routes[i].y_;
		vector<double> route_distances(n - 1);
		for (int i = 0; i < n - 1; i++)
			route_distances[i] = euclidean_distance(routes[i], routes[i + 1]);
		for (int i = 0; i < m; i++)
			cin >> places[i].x_ >> places[i].y_;

		int nr_vertices = n + m + 2;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		// 0 - (m - 1): Ralph's interesting place vertices
		// m - (m + n - 1) : Bob's route vertices, 
		//	i-th vertex represents the path from (x(i), y(i)) to (x(i + 1), y(i + 1))
		// n + m: source vertex, n + m + 1: sink vertex
		int source = n + m, sink = n + m + 1;
		for (int i = 0; i < m; i++) {
			// append the edges between the source and place vertices
			graph[source].push_back(edge(i, 1, 1));
			graph[i].push_back(edge(source, 1, 0));
			for (int j = 0; j < n - 1; j++) {
				// append the edges between place vertices and route vertices
				if (euclidean_distance(places[i], routes[j]) + euclidean_distance(places[i], routes[j + 1]) <=
					2.0 * route_distances[j]) {
					graph[i].push_back(edge(m + j, 1, 1));
					graph[m + j].push_back(edge(i, 1, 0));
				}
			}
		}
		for (int i = m; i < m + n; i++) {
			// append the edges between route vertices and the sink
			graph[i].push_back(edge(sink, 1, 1));
			graph[sink].push_back(edge(i, 1, 0));
		}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		cout << n + total_flow(graph, source) << endl;
		for (int i = 0; i < n - 1; i++) {
			if (i)
				cout << ' ';
			cout << routes[i].x_ << ' ' << routes[i].y_;
			const vector<edge>& edges = graph[m + i];
			int j = -1;
			for (size_t k = 0; k < edges.size(); k++)
				if (edges[k].residual && edges[k].v < m) {
					j = edges[k].v; break;
				}
			if (j != -1)
				cout << ' ' << places[j].x_ << ' ' << places[j].y_;
		}
		cout << ' ' << routes[n - 1].x_ << ' ' << routes[n - 1].y_ << endl;
		if (l)
			cout << endl;
	}
	return 0;
}

