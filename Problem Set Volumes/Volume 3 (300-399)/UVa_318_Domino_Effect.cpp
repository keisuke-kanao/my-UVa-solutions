
/*
	UVa 318 - Domino Effect

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_318_Domino_Effect.cpp

	from ACM Southwestern European Regional Contest Problem 3
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1996/problems96.html)
*/

#include <vector>
#include <set>
#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

struct edge {
	int v_;
	int l_;
	edge() {}
	edge(int v, int l) : v_(v), l_(l) {}
};

struct vertex_time {
	int v_;
	int t_;
	vertex_time() {}
	vertex_time(int v, int t) : v_(v), t_(t) {}

	bool operator<(const vertex_time& vt) const {return (t_ != vt.t_) ? t_ < vt.t_ : v_ < vt.v_;}
};

int main()
{
	for (int s = 1; ; s++) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		vector< vector<edge> > edges(n + 1);
		while (m--) {
			int a, b, l;
			scanf("%d %d %d", &a, &b, &l);
			edges[a].push_back(edge(b, l));
			edges[b].push_back(edge(a, l));
		}
		printf("System #%d\n", s);
		vector<int> times(n + 1, numeric_limits<int>::max());
			// times[i] is the time when vertex i was visited
		vector<int> parents(n + 1, -1);
		vector<bool> visited(n + 1, false);
		int max_v = 1; // vertex number that was visted last
		set <vertex_time> pq; // priority queue
		times[1] = 0;
		pq.insert(vertex_time(1, 0));
		while (!pq.empty()) {
			vertex_time u = *pq.begin();
			pq.erase(pq.begin());
			visited[u.v_] = true;
			if (times[u.v_] > times[max_v])
				max_v = u.v_;
			const vector<edge>& es = edges[u.v_];
			for (size_t i = 0, j = es.size(); i < j; i++) {
				const edge& e = es[i];
				if (!visited[e.v_] && times[e.v_] > times[u.v_] + e.l_) {
					times[e.v_] = times[u.v_] + e.l_;
					parents[e.v_] = u.v_;
					vertex_time vt(e.v_, times[e.v_]);
					pq.erase(vt); // remove vt if it has already been in the queue
					pq.insert(vt);
				}
			}
		}
#ifdef DEBUG
		puts("times");
		for (int i = 1; i <= n; i++)
			printf("%3d%c", times[i], ((!(i % 10) || i == n) ? '\n' : ' '));
		puts("parents");
		for (int i = 1; i <= n; i++)
			printf("%3d%c", parents[i], ((!(i % 10) || i == n) ? '\n' : ' '));
#endif
		int max_t = times[max_v];
		int next_max_v = -1, max_diff = -1;
		const vector<edge>& es = edges[max_v];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			const edge& e = es[i];
			if (parents[e.v_] == max_v)
				continue;
			int diff = max_t - times[e.v_];
			if (e.l_ > diff) {
				diff = e.l_ - diff;
				if (diff > max_diff) {
					next_max_v = e.v_;
					max_diff = diff;
				}
			}
		}
#ifdef DEBUG
		printf("max_v = %d, nex_max_v = %d\n", max_v, next_max_v);
#endif
		if (next_max_v == -1)
			printf("The last domino falls after %d.0 seconds, at key domino %d.\n\n", max_t, max_v);
		else {
			if (max_v < next_max_v)
				swap(max_v, next_max_v);
			printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n\n",
				max_t + static_cast<double>(max_diff) / 2.0, next_max_v, max_v);
		}
	}
	return 0;
}

