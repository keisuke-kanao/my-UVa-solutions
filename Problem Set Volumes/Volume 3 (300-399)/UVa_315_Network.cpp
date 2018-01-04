
/*
	UVa 315 - Network

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_315_Network.cpp

	from ACM Central European Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_CERC/1996/index.html)
	Note that the judge's solution (h.c, h.out) is WRONG.

	This is a problem to find articulation vertices in a graph where 
	places are vertices and connections are edges between them.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

struct vertex_state {
	bool discovered; // true if the vertex has been found
	bool processed;	// true if the vertex has been processed
	int parent; // parent vertex
	int entry_time;
	int exit_time;
	int reachable_ancestor;	// earliest reachable ancestor vertex
	int tree_out_degree; //	outdegree in a Depth-First-Search tree

	vertex_state() : discovered(false), processed(false), parent(-1), entry_time(-1), exit_time(-1),
		reachable_ancestor(-1), tree_out_degree(0) {}
};

enum edge_types {self_edge = -1, tree_edge, back_edge, forward_edge, cross_edge};

int edge_type(int u, int v, const vector<vertex_state>& states)
{
	const vertex_state& s = states[v];
	if (s.parent == u)
		return tree_edge;
	else if (s.discovered && !s.processed)
		return back_edge;
	else if (s.processed && s.entry_time > states[u].entry_time)
		return forward_edge;
	else if (s.processed && s.entry_time < states[u].entry_time)
		return cross_edge;
	else
		return self_edge;
}

void process_edge(int u, int v, vector<vertex_state> & states)
{
	int type = edge_type(u, v, states);
	if (type == tree_edge)
		states[u].tree_out_degree++;
	else if (type == back_edge && states[u].parent != v) {
		if (states[v].entry_time < states[states[u].reachable_ancestor].entry_time)
			states[u].reachable_ancestor = v;
	}
}

void process_vertex_late(int u, vector<vertex_state>& states, set<int>& articulation_vertices)
{
	int parent = states[u].parent; // parent vertex
	if (parent < 0) { // u is a root of a DFS tree
		if (states[u].tree_out_degree> 1) {
#ifdef DEBUG
			cout << "root articulation vertex: " << u << endl;
#endif
			articulation_vertices.insert(u);
		}
		return;
	}
	bool root = states[parent].parent < 0; // true if the grand-parent of u is a root
	if (states[u].reachable_ancestor == parent && !root) {
#ifdef DEBUG
		cout << "parent articulation vertex: " << parent << endl;
#endif
		articulation_vertices.insert(parent);
	}
	if (states[u].reachable_ancestor == u) {
		if (!root) {
#ifdef DEBUG
			cout << "bridge articulation vertex: " << parent << endl;
#endif
			articulation_vertices.insert(parent);
		}
		if (states[u].tree_out_degree > 0) { //* u is not a leaf
#ifdef DEBUG
			cout << "bridge articulation vertex: " << u << endl;
#endif
			articulation_vertices.insert(u);
		}
	}
	int time_u = states[states[u].reachable_ancestor].entry_time; // earliest reachable time for u
	int time_parent = states[states[parent].reachable_ancestor].entry_time; // earliest reachable time for parent
	if (time_u < time_parent)
		states[parent].reachable_ancestor = states[u].reachable_ancestor;
}

void dfs(const vector< vector<int> >& graph, int u, int& time, vector<vertex_state> & states, set<int>& articulation_vertices)
{
	states[u].discovered = true;
	states[u].entry_time = ++time;
	states[u].reachable_ancestor = u;
	for (int i = 0; i < graph[u].size(); i++) {
		int v = graph[u][i];
		if (!states[v].discovered) {
			states[v].parent = u;
			process_edge(u, v, states);
			dfs(graph, v, time, states, articulation_vertices);
		}
		else if (!states[v].processed)
			process_edge(u, v, states);
	}
	process_vertex_late(u, states, articulation_vertices);
	states[u].processed = true;
	states[u].exit_time = ++time;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;
	while (true) {
		getline(cin, line);
		iss.str(line);
		int nr_places;
		iss >> nr_places;
		iss.clear();
		if (!nr_places)
			break;
		vector< vector<int> > graph(nr_places);
		while (true) {
			getline(cin, line);
			iss.str(line);
			int u, v;
			iss >> u;
			if (!u) {
				iss.clear();
				break;
			}
			u--;
			while (iss >> v) {
				v--;
				graph[u].push_back(v); graph[v].push_back(u);
			}
			iss.clear();
		}
		// find articulation vertices
		vector<vertex_state> states(nr_places);
		set<int> articulation_vertices;
		for (vector<vertex_state>::iterator i = states.begin(); i != states.end(); i++)
			if (!i->discovered) {
				int time = 0;
				dfs(graph, distance(states.begin(), i), time, states, articulation_vertices);
			}
		cout << articulation_vertices.size() << endl;
	}
	return 0;
}

