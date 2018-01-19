/*
	10.5.2 The Necklace
	PC/UVa IDs: 111002/10054, Popularity: B, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10054_The_Necklace.cpp
*/

/*
	Generate an undirected unweighted graph where vertices are colors and edges are beads.
	Apply Eulerian circuit algorithm to the graph.

	An undirected graph has an eulerian circuit if and only if it is connected and 
	each vertex has an even degree (degree is the number of edges that are adjacent to that vertex).
*/

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
using namespace std;

bool vertices_have_even_degree(int v_min, int v_max, const vector<int>& degrees)
{
	for (int i = v_min; i <= v_max; i++)
		if (degrees[i] & 1) // vetex i has odd degree
			return false;
	return true;
}

void _vertices_connected(int v_min, int v_max, int v, const vector< vector<int> >& graph, vector<bool>& discovered)
{
	// do a depth-first-search and see if all of the vertices are connected
	discovered[v] = true;
	const vector<int>& neighbors = graph[v];
	for (int w = v_min; w <= v_max; w++)
		if (neighbors[w] && !discovered[w]) {
			discovered[w] = true;
			_vertices_connected(v_min, v_max, w, graph, discovered);
		}
}

bool vertices_connected(int v_min, int v_max, const vector<int>& degrees, const vector< vector<int> >& graph)
{
	// do a depth-first-search and see if all of the vertices are connected
	vector<bool> discovered(graph.size(), false);
	_vertices_connected(v_min, v_max, v_min, graph, discovered);
	for (int i = v_min; i <= v_max; i++)
		if (degrees[i] && !discovered[i]) // vertex i is not connected
			return false;
	return true;
}

void construct_eulerian_circuit(int v_min, int v_max, int v, vector< vector<int> >& graph, list<int>& circut)
// cycle finding algorithm in O(|V| + |E|)
{
	for (int w = v_min; w <= v_max; w++) {
		if (graph[v][w]) {
			graph[v][w]--;
			graph[w][v]--;
			construct_eulerian_circuit(v_min, v_max, w, graph, circut);
		}
	}
	circut.push_front(v);
}

int main(int /* argc */, char** /* argv */)
{
	const int nr_colors = 50;
	int cases;
	cin >> cases;
	for (int c = 0; c < cases; c++) {
		int nr_beads;
		cin >> nr_beads;
		int v_min = nr_colors, v_max = 0;
		vector<int> degrees(nr_colors + 1, 0);
			// degrees[0] is not used
		vector< vector<int> > graph(nr_colors + 1, vector<int>(nr_colors + 1, 0));
			// graph[0][0 - nr_colors] and graph[0 - nr_colors][0] are not used
		for (int i = 0; i < nr_beads; i++) {
			int c1, c2;
			cin >> c1 >> c2;
			v_min = min(v_min, min(c1, c2));
			v_max = max(v_max, max(c1, c2));
			degrees[c1]++; degrees[c2]++;
			graph[c1][c2]++; graph[c2][c1]++;
		}
		cout << "Case #" << c + 1 << endl;
		if (!vertices_have_even_degree(v_min, v_max, degrees) || !vertices_connected(v_min, v_max, degrees, graph))
			cout << "some beads may be lost\n";
		else {
			list<int> circut;
			construct_eulerian_circuit(v_min, v_max, v_min, graph, circut);
#ifndef ONLINE_JUDGE
			assert(circut.front() == circut.back());
#endif
			list<int>::const_iterator i = circut.begin(), j = circut.begin();
			for (j++; j != circut.end(); i++, j++) {
				cout << *i << ' ' << *j << endl;
#ifndef ONLINE_JUDGE
				assert(nr_beads-- > 0);
#endif
			}
#ifndef ONLINE_JUDGE
			assert(nr_beads == 0);
#endif
		}
		if (c < cases - 1)
			cout << endl; // print a blank line between two successive test cases
	}
	return 0;
}

