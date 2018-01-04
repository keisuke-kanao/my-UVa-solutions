
/*
	UVa 11635 - Hotel booking

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11635_Hotel_booking.cpp

	This is another accepted solution, with ranking 21.
*/

#include <vector>
#include <set>
#include <limits>
#include <cstdio>
using namespace std;

const int n_max = 10000, h_max = 100, minutes_max = 10 * 60;

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

bool hotels[n_max + 1], visited[n_max + 1][h_max + 1];
vector<edge> edges[n_max + 1];
int distances[n_max + 1][h_max + 1];
	// distances[i][j] is the min. minutes to reach city i after spending j nights in the hotels

struct distance_comparator {
	bool operator() (const pair<int, int>& i, const pair<int, int>& j) const
	{
		if (i.second != j.second)
			return i.second < j.second;
		int di = distances[i.first][i.second], dj = distances[j.first][j.second];
		return (di != dj) ? di < dj : i.first < j.first;
	}
};

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int h;
		scanf("%d", &h);
		for (int i = 1; i <= n; i++) {
			hotels[i] = false;
			edges[i].clear();
			for (int j = 0; j <= h; j++) {
				visited[i][j] = false;
				distances[i][j] = numeric_limits<int>::max();
			}
		}
		for (int i = 0; i < h; i++) {
			int c;
			scanf("%d", &c);
			hotels[c] = true;
		}
		int m;
		scanf("%d", &m);
		while (m--) {
			int a, b, t;
			scanf("%d %d %d", &a, &b, &t);
			edges[a].push_back(edge(b, t));
			edges[b].push_back(edge(a, t));
		}
		// apply the Dijkstra's shortest path algorithm
		set<pair<int, int>, distance_comparator> pq; // priority queue
		distances[1][0] = 0;
		pq.insert(make_pair(1, 0));
		int min_d = -1;
		while(!pq.empty()) {
			pair<int, int> p = *pq.begin();
			pq.erase(pq.begin());
			int u = p.first, d = p.second, t = distances[u][d];
			visited[u][d] = true;
#ifdef DEBUG
			printf("%d %d %d\n", u, d, t);
#endif
			if (u == n) {
				min_d = d;
				break;
			}
			const vector<edge>& es = edges[u];
			for (size_t i = 0, j = es.size(); i < j; i++) {
				int v = es[i].v_, w = es[i].w_;
				if (t + w <= minutes_max && !visited[v][d] && t + w < distances[v][d]) {
					pair<int, int> q = make_pair(v, d);
					pq.erase(q);
					distances[v][d] = t + w;
#ifdef DEBUG
					printf("  %d %d %d\n", v, d, distances[v][d]);
#endif
					pq.insert(q);
				}
				if (hotels[u] && d < h && w <= minutes_max && !visited[v][d + 1] && w < distances[v][d + 1]) {
					pair<int, int> q = make_pair(v, d + 1);
					pq.erase(q);
					distances[v][d + 1] = w;
#ifdef DEBUG
					printf("  %d %d %d\n", v, d + 1, distances[v][d + 1]);
#endif
					pq.insert(q);
				}
			}
		}
		printf("%d\n", min_d);
	}
	return 0;
}

