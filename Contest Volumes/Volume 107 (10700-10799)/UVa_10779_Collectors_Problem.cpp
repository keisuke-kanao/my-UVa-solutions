
/*
	UVa 10779 - Collectors Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10779_Collectors_Problem.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

const int infinite = numeric_limits<int>::max();

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

/*
The trick is to build a graph, such that every path in it will correspond to a series of exchanges of duplicate stickers, 
starting with Bob giving away one of his duplicates, and ending with him receiving a new sticker.

The graph has n subgraphs, one for each person (including Bob).

i-th subgraph has the following vertices:
  m input vertices In(i, j) and m output vertices Out(i, j), where j=1..m (j denotes sticker's type)
  a source s(i) and a sink t(i)

And the edges are:
  from In(i, j) to t(i) of capacity 1 for all j's such that i-th person doesn't yet have j-th sticker
  (a flow on this edge means that i-th person decides to buy j-th sticker)

  from t(i) to s(i) of infinite capacity, if i > 1.
  (if i=1, s(1) and t(1) will be source and sink; if i>1, we actually need only one vertex here, but let's keep two just for consistency)

  from s(i) to Out(i, j) of capacity equal to the number of duplicate stickers of type j that i-th person has;
  (each unit of flow here corresponds to a sale of j-th sticker by i-th person)

  an edge from Out(i, k) to In(j, k) for all i,j,k of capacity 1

  The value of maximum flow from s(1) to t(1) should give you the maximum number of additional stickers 
  that Bob can gain by trading his duplicate stickers.
*/

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int n, m, i, j, k;
		cin >> n >> m;
		int nr_vertices = n * (2 * m + 2);
		vector< vector<edge> > graph(nr_vertices);
/*
	vertices are:
		i:								s(i)
		n + i:							t(i)
		n * 2 + m * 2 * i + j:			In(i, j)
		n * 2 + m * (2 * i + 1) + j:	Out(i, j)
*/
		int bobs_sticker = 0;
		for (i = 0; i < n; i++) {
			const int m_max = 25;
			int stickers[m_max];
			for (j = 0; j < m; j++)
				stickers[j] = 0;
			cin >> j;
			while (j--) {
				cin >> k;
				k--;
				if (!i && !stickers[k])
					bobs_sticker++;
				stickers[k]++;
			}
			if (i) {
				// from t(i) to s(i) of infinite capacity
				graph[n + i].push_back(edge(i, infinite, infinite));
				graph[i].push_back(edge(n + i, infinite, 0));
			}
			for (j = 0; j < m; j++) {
				if (stickers[j] > 1) {
					// from s(i) to Out(i, j) of capacity equal to the number of duplicate stickers of type j that i-th person has
					graph[i].push_back(edge(n * 2 + m * (2 * i + 1) + j, stickers[j] - 1, stickers[j] - 1));
					graph[n * 2 + m * (2 * i + 1) + j].push_back(edge(i, stickers[j] - 1, 0));
				}
				else if (!stickers[j]) {
					// from In(i, j) to t(i) of capacity 1 for all j's such that i-th person doesn't yet have j-th sticker
					graph[n * 2 + m * 2 * i + j].push_back(edge(n + i, 1, 1));
					graph[n + i].push_back(edge(n * 2 + m * 2 * i + j, 1, 0));
				}
			}
			for (j = i + 1; j < n; j++)
				for (k = 0; k < m; k++) {
					// an edge from Out(i, k) to In(j, k) for all i,j,k of capacity 1
					graph[n * 2 + m * (2 * i + 1) + k].push_back(edge(n * 2 + m * 2 * j + k, 1, 1));
					graph[n * 2 + m * 2 * j + k].push_back(edge(n * 2 + m * (2 * i + 1) + k, 1, 0));
					graph[n * 2 + m * (2 * j + 1) + k].push_back(edge(n * 2 + m * 2 * i + k, 1, 1));
					graph[n * 2 + m * 2 * i + k].push_back(edge(n * 2 + m * (2 * j + 1) + k, 1, 0));
				}
		}
		netflow(graph, 0, n);
		cout << "Case #" << t << ": " << bobs_sticker + total_flow(graph, 0) << endl;
	}
	return 0;
}

