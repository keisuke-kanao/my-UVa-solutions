
/*
	UVa 10917 - A Walk Through the Forest

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10917_A_Walk_Through_the_Forest.cpp
*/

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <limits>
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

int dijkstra_shortest_path(int n, int start, int end, const vector< vector<edge> >& edges, vector<int>& distances)
{
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
	return distances[end];
}

void bfs(int n, int start, const vector< vector<edge> >& edges, const vector<int>& distances, vector<int>& routes)
{
	routes[start] = 1;
	vector<bool> visited(n, false);
	priority_queue<int, vector<int>, distance_comparator> pq(distances);
	visited[start] = true;
	pq.push(start);
	while (!pq.empty()) {
		int u = pq.top(); pq.pop();
		const vector<edge>& es = edges[u];
		for (size_t i = 0, j = es.size(); i < j; i++) {
			int v = es[i].v_;
			if (distances[u] > distances[v]) {
				if (visited[v])
					routes[v] += routes[u];
				else {
					visited[v] = true;
					routes[v] = routes[u];
					pq.push(v);
				}
			}
		}
	}
}

int main()
{
	while (true) {
		int n, m;
		cin >> n;
		if (!n)
			break;
		cin >> m;
		vector< vector<edge> > edges(n);
		while (m--) {
			int u, v, d;
			cin >> u >> v >> d;
			u--; v--;
			edges[u].push_back(edge(v, d));
			edges[v].push_back(edge(u, d));
		}
		vector<int> distances(n, numeric_limits<int>::max());
		dijkstra_shortest_path(n, 1, 0, edges, distances);
		vector<int> routes(n, 0);
		bfs(n, 0, edges, distances, routes);
		cout << routes[1] << endl;
	}
	return 0;
}

