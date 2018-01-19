
/*
	9.6.1 Bicoloring
	PC/UVa IDs: 110901/10004, Popularity: A, Success rate: high Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10004_Bicoloring.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum vertex_state {initialized = -1, discovered, processed};
enum vertex_color {unknown = -1, red, black};

bool bicolor(const vector< vector<int> >&matrix, vector<vertex_state>& states, vector<vertex_color>& colors)
{
/*
	Do a breadth-first search.
	When processing a newly discovered vertex, apply for the vertex the color that is different from its parent.
	When processing an edge, see whether it is adjacent to the same color vertices or not.
*/
	queue<int> vq; // vertex queue
	states[0] = processed;
	colors[0] = red;
	vq.push(0);
	while (!vq.empty()) {
		int v = vq.front(); vq.pop();
		for (int i = 0; i < matrix[v].size(); i++)
			if (matrix[v][i]) {
				if (states[i] == initialized) {
					states[i] = discovered;
					colors[i] = (colors[v] == red) ? black : red; // apply for the vertex the color that is different from its parent
					vq.push(i);
				}
				else if (states[i] == discovered) {
					if (colors[i] == colors[v]) // an edge is adjacent to the same color vertices
						return false;
				}
			}
	}
	return true;
}

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int n; // number of vertices
		cin >> n;
		if (!n)
			break;
		vector< vector<int> > matrix(n, vector<int>(n, 0)); // adjacency matrix of n vertices
		int l; // number of edges
		cin >> l;
		for (int i = 0; i < l; i++) {
			int u, v;
			cin >> u >> v;
			matrix[u][v] = matrix[v][u] = 1;
		}
		vector<vertex_state> states(n, initialized);
		vector<vertex_color> colors(n, unknown);
		cout << (bicolor(matrix, states, colors) ? "BICOLORABLE.\n" : "NOT BICOLORABLE.\n");
	}
	return 0;
}

