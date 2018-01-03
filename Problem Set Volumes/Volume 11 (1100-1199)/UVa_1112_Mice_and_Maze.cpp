
/*
	UVa 1112 - Mice and Maze

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1112_Mice_and_Maze.cpp
*/

#include <iostream>
#include <vector>
#include <set>
#include <limits>
using namespace std;

struct edge {
	int v_;
	int w_;
	edge() {}
	edge(int v, int w) : v_(v), w_(w) {}
};

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int n, e, t, m;
		cin >> n >> e >> t >> m;
		vector< vector<edge> > edges(n + 1);
		while (m--) {
			int u, v, w;
			cin >> u >> v >> w;
			edges[v].push_back(edge(u, w));
				// reverse the edge direction since the edges will be examined from the destination vertex
		}

		// apply Dijkstra's shortest path
		vector<int> distances(n + 1, numeric_limits<int>::max());
		vector<bool> visited(n + 1, false);
		set<int> pq; // priority queue
		distances[e] = 0;
		pq.insert(e);
		while (!pq.empty()) {
			int u = *pq.begin();
			pq.erase(pq.begin());
			visited[u] = true;
			const vector<edge>& es = edges[u];
			for (size_t i = 0, j = es.size(); i < j; i++) {
				const edge& e = es[i];
				if (!visited[e.v_] && distances[e.v_] > distances[u] + e.w_) {
					distances[e.v_] = distances[u] + e.w_;
					pq.erase(e.v_); // remove vt if it has already been in the queue
					pq.insert(e.v_);
				}
			}
		}
		int nr = 0;
		for (int i = 1; i <= n; i++)
			if (distances[i] <= t)
				nr++;
		cout << nr << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

