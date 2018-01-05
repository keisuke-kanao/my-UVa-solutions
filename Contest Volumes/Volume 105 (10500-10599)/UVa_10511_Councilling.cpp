
/*
	UVa 10511 - Councilling

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10511_Councilling.cpp
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
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

struct resident {
	string s_;
	int party_;
	vector<int> clubs_;
};

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int T;
	iss >> T;
	iss.clear();
	getline(cin, line);
	while (T--) {
		vector<resident> residents;
		map<string, int> parties, clubs;
		while (true) {
			getline(cin, line);
			if (line.empty())
				break;
			iss.str(line);
			residents.push_back(resident());
			resident& r = residents.back();
			iss >> r.s_;
			string s;
			iss >> s;
			parties.insert(make_pair(s, static_cast<int>(parties.size())));
			r.party_ = parties[s];
			while (iss >> s) {
				clubs.insert(make_pair(s, static_cast<int>(clubs.size())));
				r.clubs_.push_back(clubs[s]);
			}
			iss.clear();
		}
		int nr_residents = static_cast<int>(residents.size()), nr_clubs = static_cast<int>(clubs.size()),
			nr_parties = static_cast<int>(parties.size());
		int nr_vertices = nr_clubs + nr_residents + nr_parties + 2,
			source = nr_clubs + nr_residents + nr_parties, sink = nr_clubs + nr_residents + nr_parties + 1;
		// indices are:
		// 0 - (nr_clubs - 1) : club vertices, clubs + (nr_clubs + nr_residents - 1): resident vertices,
		// (nr_clubs + nr_residents + nr_parties - 1): party vertices
		vector< vector<edge> > graph(nr_vertices);
		// append the edges from the source to club vertices
		for (int i = 0; i < nr_clubs; i++)
			add_edge(source, i, 1, graph);
		for (int i = 0; i < nr_residents; i++) {
			const resident& r = residents[i];
			// append the edges from the club vertices to the resident vertices
			for (int j = 0, je = static_cast<int>(r.clubs_.size()); j < je; j++)
				add_edge(r.clubs_[j], nr_clubs + i, 1, graph);
			// append the edges from the resident vertices to the party vertices
			add_edge(nr_clubs + i, nr_clubs + nr_residents + r.party_, 1, graph);
		}
		// append the edgs from the party vertices to the sink
		for (int i = 0, c = (nr_clubs - 1) / 2; i < nr_parties; i++)
			add_edge(nr_clubs + nr_residents + i, sink, c, graph);
		netflow(graph, source, sink); // apply Ford-Fulkerson's augmenting path algorithm
		if (total_flow(graph, source) == nr_clubs) {
			vector<string> club_indices(nr_clubs);
			for (map<string, int>::const_iterator ci = clubs.begin(), ce = clubs.end(); ci != ce; ++ci)
				club_indices[ci->second] = ci->first;
			for (int i = 0; i < nr_clubs; i++) {
				const vector<edge>& edges = graph[i];
				for (int j = 0, je = static_cast<int>(edges.size()); j < je; j++)
					if (edges[j].flow) {
						cout << residents[edges[j].v - nr_clubs].s_ << ' ' << club_indices[i] << endl;
						break;
					}
			}
		}
		else
			puts("Impossible.");
		if (T)
			putchar('\n');
	}
	return 0;
}

