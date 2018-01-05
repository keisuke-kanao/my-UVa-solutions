
/*
	UVa 10594 - Data Flow

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10594_Data_Flow.cpp

	Another accepted solution.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const long long infinite = 1000000000000000000;

struct edge {
    int u_, v_;
	long long weight_;
	long long flow_;
};

struct vertex_state {
	long long distance_;
	int parent_;

	vertex_state() : distance_(infinite), parent_(-1) {}
};

void bellman_ford(int n, int start, const vector<edge>& edges, vector<vertex_state>& states)
{
	states[start].distance_ = 0;
	for (int i = 0, ie = n - 1; i < ie; i++)
		for (size_t j = 0, je = edges.size(); j < je; j++) {
			const edge& e = edges[j];
			if (e.flow_) {
				long long d = (states[e.u_].distance_);
				if (d + e.weight_ < states[e.v_].distance_) {
					states[e.v_].distance_ = states[e.u_].distance_ + e.weight_;
					states[e.v_].parent_ = static_cast<int>(j);
				}
			}
		}
}

pair<long long, long long> mincost_maxflow(int n, vector<edge>& edges, int source, int sink)
{
	long long flow = 0, cost = 0;
	while (true) {
		vector<vertex_state> states(n);
		bellman_ford(n, source, edges, states); // Shortest Path Faster Algorithm
		if (states[sink].distance_ == infinite)
			break;
		long long augmented = infinite;
		for (int u = states[sink].parent_; u != -1; u = states[edges[u].u_].parent_)
			if (edges[u].flow_ < augmented)
				augmented = edges[u].flow_;
		for (int u = states[sink].parent_; u != -1; u = states[edges[u].u_].parent_) {
			edges[u].flow_ -= augmented;
			edges[u ^ 1].flow_ += augmented; // residual edge
		}
		flow += augmented;
		cost += augmented * states[sink].distance_;
//		cout << flow << ' ' << cost << endl;
    }
	return make_pair(flow, cost);
}

inline void add_edge(int ei, int u, int v, long long weight, long long flow, vector<edge>& edges)
{
	edges[ei].u_ = u; edges[ei].v_ = v; edges[ei].weight_ = weight; edges[ei].flow_ = flow;
}

int main()
{
	int N, M;
	while (cin >> N >> M) {
		vector< pair< pair<int, int>, long long > > links(M);
		for (int i = 0; i < M; i++)
			cin >> links[i].first.first >> links[i].first.second >> links[i].second;
		long long D, K;
		cin >> D >> K;
		vector<edge> edges(M * 4 + 2);
		add_edge(0, 0, 1, 0, D, edges);
		add_edge(1, 1, 0, 0, 0, edges);
		for (int i = 0; i < M; i++) {
			int u = links[i].first.first, v = links[i].first.second;
			long long w = links[i].second;
			add_edge(2 + i * 4, u, v, w, K, edges);
			add_edge(3 + i * 4, v, u, -w, 0, edges);
			add_edge(4 + i * 4, v, u, w, K, edges);
			add_edge(5 + i * 4, u, v, -w, 0, edges);
		}
		pair<long long, long long> result = mincost_maxflow(N + 1, edges, 0, N);
		if (result.first == D)
			cout << result.second << endl;
		else
			cout << "Impossible.\n";
    }
    return 0;
}

