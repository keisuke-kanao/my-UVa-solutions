
/*
	UVa 558 - Wormholes

	To build using Visucal Studio 2008:
		cl -EHsc UVa_558_Wormholes.cpp
*/

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct edge {
	int u_; // source vertex
	int v_; // destination vertex
	int weight_;

	edge() : u_(-1), v_(-1), weight_(-1) {}
	edge(int u, int v, int weight) : u_(u), v_(v), weight_(weight) {}
};

bool bellman_ford(int n, int source, const vector<edge>& edges)
{
	// initialize the graph
	vector<int> distances(n, numeric_limits<int>::max());
	distances[source] = 0;
	// relax the edges repeatedly
	for (int i = 0; i < n - 1; i++)
		for (size_t j = 0, je = edges.size(); j < je; j++) {
			const edge& e = edges[j];
			if (distances[e.u_] + e.weight_ < distances[e.v_])
				distances[e.v_] = distances[e.u_] + e.weight_;
		}
	// check for negative-weight cycles
	for (size_t i = 0, ie = edges.size(); i < ie; i++) {
		const edge& e = edges[i];
		if (distances[e.u_] + e.weight_ < distances[e.v_])
			return true; // the graph contains a negative-weight cycle
	}
	return false;
}

int main()
{
	int c;
	cin >> c;
	while (c--) {
		int n, m;
		cin >> n >> m;
		vector<edge> edges(m);
		for (int i = 0; i < m; i++)
			cin >> edges[i].u_ >> edges[i].v_ >> edges[i].weight_;
		cout << ((bellman_ford(n, 0, edges)) ? "possible\n" : "not possible\n");
	}
	return 0;
}

