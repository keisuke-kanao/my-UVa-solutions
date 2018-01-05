
/*
	UVa 10269 - Adventure of Super Mario

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10269_Adventure_of_Super_Mario.cpp
*/

#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int A_max = 50, B_max = 50, n_max = A_max + B_max, L_max = 500, K_max = 10;

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

int matrix[n_max + 1][n_max + 1];
bool visited[n_max + 1], dvisited[n_max + 1][K_max + 1];
vector<edge> edges[n_max + 1];
int distances[n_max + 1][K_max + 1];
	// distances[i][j] is the min. time to vertex i using super-runs j times

struct distance_comparator {
	bool operator() (const pair<int, int>& i, const pair<int, int>& j) const
	{
		int di = distances[i.first][i.second], dj = distances[j.first][j.second];
		if (di != dj)
			return di < dj;
		return (i.second != j.second) ? i.second < j.second : i.first < j.first;
	}
};

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int A, B, M, L, K;
		scanf("%d %d %d %d %d", &A, &B, &M, &L, &K);
		int n = A + B;
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			for (int j = 1; j <= n; j++)
				matrix[i][j] = numeric_limits<int>::max();
			for (int j = 0; j <= K; j++) {
				dvisited[i][j] = false;
				distances[i][j] = numeric_limits<int>::max();
			}
		}
		while (M--) {
			int Xi, Yi, Li;
			scanf("%d %d %d", &Xi, &Yi, &Li);
			matrix[Xi][Yi] = matrix[Yi][Xi] = Li;
			edges[Xi].push_back(edge(Yi, Li));
			edges[Yi].push_back(edge(Xi, Li));
		}

		// apply the Floyd-Warshall algorithm
		for (int k = 1; k <= A; k++)
			for (int i = 1; i <= n; i++)
				if (matrix[i][k] != numeric_limits<int>::max())
					for (int j = 1; j <= n; j++)
					if (matrix[k][j] != numeric_limits<int>::max())
						matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);

		// add the edges where super-running can be used
		for (int i = 1; i <= n - 1; i++)
			for (int j = i + 1; j <= n; j++)
				if (matrix[i][j] <= L) {
#ifdef DEBUG
					printf("s %d %d %d\n", i, j, matrix[i][j]);
#endif
					edges[i].push_back(edge(j, 0));
					edges[j].push_back(edge(i, 0));
				}

		// apply the Dijkstra's shortest path algorithm
		set<pair<int, int>, distance_comparator> pq; // priority queue
		distances[n][0] = 0;
		pq.insert(make_pair(n, 0));
		int min_t = numeric_limits<int>::max();
		while(!pq.empty()) {
			pair<int, int> p = *pq.begin();
			pq.erase(pq.begin());
			int u = p.first, k = p.second, t = distances[u][k];
			dvisited[u][k] = true;
#ifdef DEBUG
			printf("%d %d %d\n", u, k, t);
#endif
			if (u == 1) {
				min_t = t;
				break;
			}
			const vector<edge>& es = edges[u];
			for (size_t i = 0, j = es.size(); i < j; i++) {
				int v = es[i].v_, w = es[i].w_;
				if (w && !dvisited[v][k] && t + w < distances[v][k]) { // a walk edge
					pair<int, int> q = make_pair(v, k);
					pq.erase(q);
					distances[v][k] = t + w;
#ifdef DEBUG
					printf("  %d %d %d\n", v, k, distances[v][k]);
#endif
					pq.insert(q);
				}
				if (!w && k < K && !dvisited[v][k + 1] && t < distances[v][k + 1]) { // a super-running edge
					pair<int, int> q = make_pair(v, k + 1);
					pq.erase(q);
					distances[v][k + 1] = t;
#ifdef DEBUG
					printf("  %d %d %d\n", v, k + 1, distances[v][k + 1]);
#endif
					pq.insert(q);
				}
			}
		}
		printf("%d\n", min_t);
	}
	return 0;
}

