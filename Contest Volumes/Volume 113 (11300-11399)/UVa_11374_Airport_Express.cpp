
/*
	UVa 11374 - Airport Express

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11374_Airport_Express.cpp
*/

#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <limits>
#include <cstdio>
using namespace std;

const int N_max = 500;

struct edge {
	int v_;
	int w_;
	int commercial_; // 1 for Commercial-Xpress, 0 for Economy-Xpress
	edge(int v, int w, int commercial) : v_(v), w_(w), commercial_(commercial) {}
};

vector<edge> edges[N_max + 1];
bool dvisited[N_max + 1][2];
int distances[N_max + 1][2];
	// distances[i][0/1] is the min. time to vertex i using Commercial-Xpress (1) or not (0)

struct path {
	int u_, commercial_;
} paths[N_max + 1][2];

struct distance_comparator {
	bool operator() (const pair<int, int>& i, const pair<int, int>& j) const
	{
		int di = distances[i.first][i.second], dj = distances[j.first][j.second];
		if (di != dj)
			return di < dj;
		return (i.second != j.second) ? i.second < j.second : i.first < j.first;
	}
};

void print_path(int u, int c, int& cu)
{
	if (paths[u][c].u_ == -1)
		printf("%d", u);
	else {
		if (c && !paths[u][c].commercial_)
			cu = paths[u][c].u_;
		print_path(paths[u][c].u_, paths[u][c].commercial_, cu);
		printf(" %d", u);
	}
}

int main()
{
	int N, S, E;
	bool printed = false;
	while (scanf("%d %d %d", &N, &S, &E) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		for (int i = 1; i <= N; i++) {
			edges[i].clear();
			dvisited[i][0] = dvisited[i][1] = false;
			distances[i][0] = distances[i][1] = numeric_limits<int>::max();
		}
		int M;
		scanf("%d", &M);
		while (M--) {
			int X, Y, Z;
			scanf("%d %d %d", &X, &Y, &Z);
			edges[X].push_back(edge(Y, Z, 0));
			edges[Y].push_back(edge(X, Z, 0));
		}
		int K;
		scanf("%d", &K);
		while (K--) {
			int X, Y, Z;
			scanf("%d %d %d", &X, &Y, &Z);
			edges[X].push_back(edge(Y, Z, 1));
			edges[Y].push_back(edge(X, Z, 1));
		}
		// apply the Dijkstra's shortest path algorithm
		set<pair<int, int>, distance_comparator> pq; // priority queue
		distances[S][0] = 0;
		paths[S][0].u_ = -1;
		pq.insert(make_pair(S, 0));
		int min_t, min_c;
		while(!pq.empty()) {
			pair<int, int> p = *pq.begin();
			pq.erase(pq.begin());
			int u = p.first, cc = p.second, t = distances[u][cc];
			dvisited[u][cc] = true;
#ifdef DEBUG
			printf("[%d][%d]: %d\n", u, cc, t);
#endif
			if (u == E) {
				min_t = t, min_c = cc;
				break;
			}
			const vector<edge>& es = edges[u];
			for (size_t i = 0, j = es.size(); i < j; i++) {
				int v = es[i].v_, w = es[i].w_, c = es[i].commercial_;
				if (c) {
					if (!cc && !dvisited[v][1] && t + w < distances[v][1]) {
						pair<int, int> q = make_pair(v, 1);
						pq.erase(q);
						distances[v][1] = t + w, paths[v][1].u_ = u, paths[v][1].commercial_ = cc;
#ifdef DEBUG
						printf("  [%d][1]: %d\n", v, distances[v][1]);
#endif
						pq.insert(q);
					}
				}
				else {
					if (!dvisited[v][cc] && t + w < distances[v][cc]) {
						pair<int, int> q = make_pair(v, cc);
						pq.erase(q);
						distances[v][cc] = t + w, paths[v][cc].u_ = u, paths[v][cc].commercial_ = cc;
#ifdef DEBUG
						printf("  [%d][%d]: %d\n", v, cc, distances[v][cc]);
#endif
						pq.insert(q);
					}
				}
			}
		}
		int cu = -1;
		print_path(E, min_c, cu);
		if (cu != -1)
			printf("\n%d\n", cu);
		else
			printf("\nTicket Not Used\n");
		printf("%d\n", min_t);
	}
	return 0;
}

