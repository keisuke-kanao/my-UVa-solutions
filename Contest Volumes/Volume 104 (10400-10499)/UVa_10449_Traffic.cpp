
/*
	UVa 10449 - Traffic

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10449_Traffic.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct edge {
	int u_; // source vertex
	int v_; // destination vertex
	int weight_;

	edge() : u_(-1), v_(-1), weight_(-1) {}
	edge(int u, int v, int weight) : u_(u), v_(v), weight_(weight) {}
};

void bfs(int n, int s, const vector< vector<int> >& adjacency_list, vector<bool>& in_negative_cycles)
{
	if (in_negative_cycles[s])
		return;
	in_negative_cycles[s] = true;
	vector<bool> visited(n + 1, false);
	visited[s] = true;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		const vector<int>& l = adjacency_list[u];
		for (size_t i = 0, j = l.size(); i < j; i++) {
			int v = l[i];
			if (!visited[v]) {
				in_negative_cycles[v] = true;
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

int main()
{
	int n;
	for (int sn = 1; cin >> n; sn++) {
		vector<int> busyness(n + 1);
		for (int i = 1; i <= n; i++)
			cin >> busyness[i];
		int r;
		cin >> r;
		vector< vector<int> > adjacency_list(n + 1);
		vector<edge> edges(r);
		for (int i = 0; i < r; i++) {
			cin >> edges[i].u_ >> edges[i].v_;
			int b = busyness[edges[i].v_] - busyness[edges[i].u_];
			edges[i].weight_ = b * b * b;
			adjacency_list[edges[i].u_].push_back(edges[i].v_);
		}

		// apply the Bellman-Ford's shortest path algorithm
		vector<int> distances(n + 1, numeric_limits<int>::max());
		distances[1] = 0;
		for (int i = 0; i < n - 1; i++)
			for (size_t j = 0, je = edges.size(); j < je; j++) {
				const edge& e = edges[j];
				int d = distances[e.u_];
				if (d != numeric_limits<int>::max() && d + e.weight_ < distances[e.v_])
					distances[e.v_] = d + e.weight_;
			}
		vector<bool> in_negative_cycles(n + 1, false);
		for (size_t i = 0, ie = edges.size(); i < ie; i++) {
			const edge& e = edges[i];
			if (distances[e.u_] != numeric_limits<int>::max() && distances[e.u_] + e.weight_ < distances[e.v_]) // e.u_ is in a negative cycle
				bfs(n, e.u_, adjacency_list, in_negative_cycles);
		}
#ifdef DEBUG
		for (int i = 1; i <= n; i++) {
			cout << in_negative_cycles[i];
			if (i < n)
				cout << ' ';
			else
				cout << endl;
		}
#endif

		int q;
		cin >> q;
		cout << "Set #" << sn << endl;
		while (q--) {
			int i;
			cin >> i;
			if (i <= 0 || i > n || in_negative_cycles[i] ||
				distances[i] == numeric_limits<int>::max() || distances[i] < 3)
				cout << "?\n";
			else
				cout << distances[i] << endl;
		}
	}
	return 0;
}

