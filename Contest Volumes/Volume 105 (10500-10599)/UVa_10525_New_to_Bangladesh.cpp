
/*
	UVa 10525 - New to Bangladesh?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10525_New_to_Bangladesh.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <limits>
using namespace std;

struct edge {
	int u_; // source vertex
	int v_; // destination vertex
	int t_; // time
	int l_; // length

	edge() : u_(-1), v_(-1), t_(-1), l_(-1) {}
	edge(int u, int v, int t, int l) : u_(u), v_(v), t_(t), l_(l) {}
};

pair<int, int> bellman_ford(int n, int s, int t, const vector<edge>& edges)
{
	// apply the Bellman-Ford's shortest path algorithm
	// initialize the graph
	vector< pair<int, int> > distances(n, make_pair(numeric_limits<int>::max(), numeric_limits<int>::max()));
	distances[s].first = distances[s].second = 0;
	// relax the edges repeatedly
	for (int i = 0; i < n - 1; i++)
		for (size_t j = 0, je = edges.size(); j < je; j++) {
			const edge& e = edges[j];
			long long lt = static_cast<long long>(distances[e.u_].first),
				ll = static_cast<long long>(distances[e.u_].second);
			if (lt + e.t_ < distances[e.v_].first ||
				lt + e.t_ == distances[e.v_].first && ll + e.l_ < distances[e.v_].second)
				distances[e.v_] = make_pair(distances[e.u_].first + e.t_, distances[e.u_].second + e.l_);
		}
	return distances[t];
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		vector<edge> edges(m * 2);
		for (int i = 0; i < m; i++) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			a--; b--;
			edges[i * 2].u_ = edges[i * 2 + 1].v_ = a;
			edges[i * 2].v_ = edges[i * 2 + 1].u_ = b;
			edges[i * 2].t_ = edges[i * 2 + 1].t_ = c;
			edges[i * 2].l_ = edges[i * 2 + 1].l_ = d;
		}
		int q;
		cin >> q;
		while (q--) {
			int s, t;
			cin >> s >> t;
			pair<int, int> d = bellman_ford(n, s - 1, t - 1, edges);
			if (d.first != numeric_limits<int>::max())
				cout << "Distance and time to reach destination is " << d.second << " & " << d.first << ".\n";
			else
				cout << "No Path.\n";
		}
		if (t)
			cout << endl;
	}
	return 0;
}

