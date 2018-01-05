
/*
	UVa 11367 - Full Tank?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11367_Full_Tank.cpp

	An accepted solution.
*/

#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <limits>
#include <cstdio>
using namespace std;

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

struct cost_comparator {
	vector< vector<int> >& costs_;

	cost_comparator(vector< vector< int> >& costs) : costs_(costs) {}
	bool operator() (const pair<int, int>& i, const pair<int, int>& j) const
	{
		return (costs_[i.first][i.second] != costs_[j.first][j.second]) ?
			costs_[i.first][i.second] < costs_[j.first][j.second] : i < j;
	}
};

int dijkstra_shortest_path(int n, int capacity, int start, int end, const vector< vector<edge> >& edges, const vector<int>& prices,
	vector< vector<int> >& costs)
{
	set<pair<int, int>, cost_comparator> pq(costs); // priority queue
	costs[start][0] = 0;
	pq.insert(make_pair(start, 0));
	while(!pq.empty()) {
		pair<int, int> p = *pq.begin();
		pq.erase(pq.begin());
		int u = p.first, c = p.second, cost = costs[u][c];
#ifdef DEBUG
		printf("costs[%d][%d]: %d\n", u, c, cost);
#endif
		if (u == end)
			return cost;
		if (c < capacity) {
			if (cost + prices[u] < costs[u][c + 1]) {
				pq.erase(make_pair(u, c + 1)); // remove (u, c + 1) if it has already been in the queue
				costs[u][c + 1] = cost + prices[u];
				pq.insert(make_pair(u, c + 1));
			}
		}
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i].v_, w = es[i].w_;
			if (c >= w) {
				int cc = c - w;
				if (cost < costs[v][cc]) {
					pq.erase(make_pair(v, cc)); // remove (v, cc) if it has already been in the queue
					costs[v][cc] = cost;
					pq.insert(make_pair(v, cc));
				}
			}
		}
	}
	return numeric_limits<int>::max();
}

int main()
{
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		vector<int> prices(n);
		for (int i = 0; i < n; i++)
			scanf("%d", &prices[i]);
		vector< vector<edge> > edges(n);
		while (m--) {
			int u, v, d;
			scanf("%d %d %d", &u, &v, &d);
			edges[u].push_back(edge(v, d));
			edges[v].push_back(edge(u, d));
		}
		int q;
		scanf("%d", &q);
		while (q--) {
			int c, s, e;
			scanf("%d %d %d", &c, &s, &e);
			vector< vector<int> > costs(n, vector<int>(c + 1, numeric_limits<int>::max()));
			int min_cost = dijkstra_shortest_path(n, c, s, e, edges, prices, costs);
			if (min_cost != numeric_limits<int>::max())
				printf("%d\n", min_cost);
			else
				puts("impossible");
		}
	}
	return 0;
}

