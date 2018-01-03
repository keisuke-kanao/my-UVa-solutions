
/*
	UVa 753 - A Plug for UNIX

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_753_A_Plug_for_UNIX.cpp

	from ACM East Central Regionals - 1999, Problem C
	(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1999/index.html)
*/

#include <iostream>
#include <string>
#include <map>
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

int register_name(const string& s, map<string, int>& names)
{
	map<string, int>::iterator i = names.find(s);
	if (i != names.end())
		return i->second;
	else {
		int n = static_cast<int>(names.size());
		names[s] = n;
		return n;
	}
}

void enumerate_plugs(vector<int>& d, int max_rpi, const multimap<int, int>& adapters)
{
	vector<bool> visited(max_rpi, false);
	queue<int> q;
	visited[d[0]] = true;
	q.push(d[0]);
	while (!q.empty()) {
		int r = q.front();
		q.pop();
		pair< map<int, int>::const_iterator, map<int, int>::const_iterator > result = adapters.equal_range(r);
		for (map<int, int>::const_iterator i = result.first; i != result.second; ++i) {
			if (!visited[i->second]) {
				d.push_back(i->second);
				visited[i->second] = true;
				q.push(i->second);
			}
		}
	}
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		map<string, int> names; // keys are plug names, values are their corresponding #s
		int n;
		cin >> n;
		vector<int> receptacles(n); // receptacles[i] is the # of plug
		for (int i = 0; i < n; i++) {
			string s;
			cin >> s;
			receptacles[i] = register_name(s, names);
		}
		int m;
		cin >> m; 
		vector< vector<int> > devices(m); // devices[i] is the vector of #s of plugs
			// that can be connected directly or indirectly though one ore more adapters
		for (int i = 0; i < m; i++) {
			string s;
			cin >> s >> s; // device names are discarded
			devices[i].push_back(register_name(s, names));
		}
		int k;
		cin >> k;
		multimap<int, int> adapters; // keys are receptacle #s, values are plug #s
		int max_rpi = -1;
		for (int i = 0; i < k; i++) {
			string s, t;
			cin >> s >> t;
			int ri = register_name(s, names), pi = register_name(t, names);
			max_rpi = max(max_rpi, max(ri, pi));
			adapters.insert(make_pair(ri, pi));
		}
		// for each device, enumerate the plugs that can be connected to
		for (int i = 0; i < m; i++)
			enumerate_plugs(devices[i], max_rpi, adapters);

		int nr_vertices = n + m + 2;
		vector< vector<edge> > graph(nr_vertices);
		// indices are:
		//	0 - (n - 1): receptacles vertices, n - (n + m - 1): device vertices,
		//	(n + m): source vertex, (n + m + 1): sink vertex
		int source = n + m, sink = n + m + 1;
		for (int i = 0; i < m; i++) {
			// append the edges between the source and device vertices
			graph[source].push_back(edge(i + n, 1, 1));
			graph[i + n].push_back(edge(source, 1, 0));
			for (size_t j = 0; j < devices[i].size(); j++) {
				int pi = devices[i][j];
				// append the edges between device vertices and receptacle vertices
				for (int ri = 0; ri < n; ri++)
					if (receptacles[ri] == pi) {
						graph[i + n].push_back(edge(ri, 1, 1));
						graph[ri].push_back(edge(i + n, 1, 0));
					}
			}
		}
		for (int i = 0; i < n; i++) {
			// append the edges between receptacle vertices and the sink
			graph[i].push_back(edge(sink, 1, 1));
			graph[sink].push_back(edge(i, 1, 0));
		}
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		cout << m - total_flow(graph, source) << endl;

		if (nr_cases)
			cout << endl;
	}
	return 0;
}

