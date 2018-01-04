
/*
	UVa 12047 - Highest Paid Toll

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12047_Highest_Paid_Toll.cpp
*/

#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <cstdio>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int N_max = 10000;

struct edge {
	int v_, c_;

	edge() {}
	edge(int v, int c) : v_(v), c_(c) {}
};

vector<edge> edges[N_max + 1], redges[N_max + 1];
int costs[N_max + 1], rcosts[N_max + 1];
bool visited[N_max + 1];

struct cost_comparator {
	int* costs_;
	cost_comparator(int* costs) : costs_(costs) {}
	bool operator() (int i, int j) const {
		if (costs_[i] != costs_[j])
			return costs_[i] < costs_[j];
		else
			return i < j;
	}
};

void dijkstra_shortest_path(int n, int s, const vector<edge>* edges, int* costs)
{
	for (int i = 1; i <= n; i++) {
		visited[i] = false;
		costs[i] = infinite;
	}
	set<int, cost_comparator> pq(costs); // priority queue
	costs[s] = 0.0;
	pq.insert(s);
	while (!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			const edge& e = es[i];
			if (!visited[e.v_] && costs[e.v_] > costs[u] + e.c_) {
				pq.erase(e.v_); // remove vt if it has already been in the queue
					// this must be done before updating costs[]
				costs[e.v_] = costs[u] + e.c_;
				pq.insert(e.v_);
			}
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int N, M, s, t, p;
		scanf("%d %d %d %d %d", &N, &M, &s, &t, &p);
		for (int i = 1; i <= N; i++) {
			edges[i].clear();
			redges[i].clear();
		}
		while (M--) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			edges[u].push_back(edge(v, c));
			redges[v].push_back(edge(u, c));
		}
		dijkstra_shortest_path(N, s, edges, costs);
			// costs[i] is the min. cost from s to i
#ifdef DEBUG
		for (int i = 1; i <= N; i++)
			if (costs[i] < infinite)
				printf("%d: %d ", i, costs[i]);
		putchar('\n');
#endif
		dijkstra_shortest_path(N, t, redges, rcosts);
			// rcosts[i] is the min. cost from t to i traversing the edge reversely
#ifdef DEBUG
		for (int i = 1; i <= N; i++)
			if (rcosts[i] < infinite)
				printf("%d: %d ", i, rcosts[i]);
		putchar('\n');
#endif
		int max_toll = -1;
		queue<int> q;
		for (int i = 1; i <= N; i++)
			visited[i] = false;
		visited[s] = true;
		q.push(s);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			const vector<edge> es = edges[u];
			for (size_t i = 0, e = es.size(); i < e; i++) {
				int v = es[i].v_;
				if (costs[u] < infinite && rcosts[v] < infinite) {
					int c = costs[u] + es[i].c_ + rcosts[v];
					if (c <= p)
						max_toll = max(max_toll, es[i].c_);
				}
				if (!visited[v]) {
					visited[v] = true;
					q.push(v);
				}
			}
		}
		printf("%d\n", max_toll);
	}
	return 0;
}

