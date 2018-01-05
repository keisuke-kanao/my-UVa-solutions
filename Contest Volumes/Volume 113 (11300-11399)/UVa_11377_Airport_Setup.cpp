
/*
	UVa 11377 - Airport Setup

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11377_Airport_Setup.cpp
*/

#include <vector>
#include <set>
#include <limits>
#include <cstdio>
using namespace std;

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

struct distance_comparator {
	const vector<int>& distances_;

	distance_comparator(const vector<int>& distances) : distances_(distances) {}
	bool operator() (int i, int j) const
	{
		return (distances_[i] != distances_[j]) ? distances_[i] < distances_[j] : i < j;
	}
};

int dijkstra_shortest_path(int n, int start, int end, const vector< vector<edge> >& edges)
{
	vector<int> distances(n, numeric_limits<int>::max());
	vector<bool> visited(n, false);
	set<int, distance_comparator> pq(distances); // priority queue
	distances[start] = 0;
	pq.insert(start);
	while(!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		if (u == end)
			break;
		int d = distances[u];
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i].v_, w = es[i].w_;
			if (!visited[v] && distances[v] > d + w) {
				pq.erase(v); // remove v if it has already been in the queue
				distances[v] = d + w;
				pq.insert(v);
			}
		}
	}
	return (distances[end] != numeric_limits<int>::max()) ? distances[end] : -1;
}

int main()
{
	int X;
	scanf("%d", &X);
	for (int x = 1; x <= X; x++) {
		int N, M, K;
		scanf("%d %d %d", &N, &M, &K);
		vector<int> airports(N, 1);
		while (K--) {
			int i;
			scanf("%d", &i);
			airports[i - 1] = 0;
		}
		vector< vector<edge> > edges(N);
		while (M--) {
			int u, v;
			scanf("%d %d", &u, &v);
			u--; v--;
			edges[u].push_back(edge(v, airports[v]));
			edges[v].push_back(edge(u, airports[u]));
		}
		int Q;
		scanf("%d", &Q);
		printf("Case %d:\n", x);
		while (Q--) {
			int x, y;
			scanf("%d %d", &x, &y);
			int d = dijkstra_shortest_path(N, x - 1, y - 1, edges);
			if (d != -1 && x != y)
				d += airports[x - 1];
			printf("%d\n", d);
		}
		putchar('\n');
	}
	return 0;
}

