
/*
	UVa 12144 - Almost Shortest Path

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12144_Almost_Shortest_Path.cpp
*/

#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <limits>
#include <cstdio>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int N_max = 500;

struct edge {
	int v_;
	int w_;
	bool removed_;
	edge(int v, int w) : v_(v), w_(w), removed_(false) {}
};

vector<edge> edges[N_max];
int distances[N_max];
bool visited[N_max];
vector< pair<int, int> > paths[N_max];

struct distance_comparator {
	bool operator() (int i, int j) const
	{
		return (distances[i] != distances[j]) ? distances[i] < distances[j] : i < j;
	}
};

int shortest_path(int n, int start, int end)
{
	for (int i = 0; i < n; i++)
		visited[i] = false, distances[i] = infinite, paths[i].clear();
	set<int, distance_comparator> pq; // priority queue
	int min_d = -1;
	distances[start] = 0;
	pq.insert(start);
	while(!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		int d = distances[u];
#ifdef DEBUG
		printf("%d: %d\n", u, d);
#endif
		if (u == end)
			min_d = d;
		else {
			const vector<edge>& es = edges[u];
			for (int i = 0, j = static_cast<int>(es.size()); i < j; i++) {
				int v = es[i].v_, w = es[i].w_;
				if (!visited[v] && distances[v] > d + w) {
					pq.erase(v); // remove v if it has already been in the queue
					distances[v] = d + w;
					paths[v].clear();
					paths[v].push_back(make_pair(u, i));
#ifdef DEBUG
					printf("\t%d-%d\n", u, v);
#endif
					pq.insert(v);
				}
				else if (distances[v] == d + w) {
					paths[v].push_back(make_pair(u, i));
#ifdef DEBUG
					printf("\t%d-%d\n", u, v);
#endif
				}
			}
		}
	}
	return min_d;
}

void mark_shortest_paths(int n, int end)
{
	for (int i = 0; i < n; i++)
		visited[i] = false;
	queue<int> q;
	visited[end] = true;
	q.push(end);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vector< pair<int, int> >& ps = paths[u];
		for (int i = 0, j = static_cast<int>(ps.size()); i < j; i++) {
			int v = ps[i].first;
#ifdef DEBUG
			printf("%d-%d\n", v, edges[v][ps[i].second].v_);
#endif
			edges[v][ps[i].second].removed_ = true;
			if (!visited[v]) {
				visited[v] = true;
				q.push(v);
			}
		}
	}
}

int allmost_shortest_path(int n, int start, int end)
{
	for (int i = 0; i < n; i++)
		visited[i] = false, distances[i] = infinite;
	set<int, distance_comparator> pq; // priority queue
	distances[start] = 0;
	pq.insert(start);
	while(!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		int d = distances[u];
		if (u == end)
			return d;
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			if (es[i].removed_)
				continue;
			int v = es[i].v_, w = es[i].w_;
			if (!visited[v] && distances[v] > d + w) {
				pq.erase(v); // remove v if it has already been in the queue
				distances[v] = d + w;
				pq.insert(v);
			}
		}
	}
	return -1;
}

int main()
{
	while (true) {
		int N, M;
		scanf("%d %d", &N, &M);
		if (!N)
			break;
		for (int i = 0; i < N; i++)
			edges[i].clear();
		int S, D;
		scanf("%d %d", &S, &D);
		while (M--) {
			int U, V, P;
			scanf("%d %d %d", &U, &V, &P);
			edges[U].push_back(edge(V, P));
		}
		int d = shortest_path(N, S, D);
#ifdef DEBUG
		printf("%d\n", d);
#endif
		if (d != -1) {
			mark_shortest_paths(N, D);
			d = allmost_shortest_path(N, S, D);
		}
		printf("%d\n", d);
	}
	return 0;
}

