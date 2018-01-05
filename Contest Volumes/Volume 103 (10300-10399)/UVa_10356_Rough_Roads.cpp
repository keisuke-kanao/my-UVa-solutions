
/*
	UVa 10356 - Rough Roads

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10356_Rough_Roads.cpp
*/

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <limits>
using namespace std;

const int n_max = 500;

struct edge {
	int v_;
	int w_;
	edge(int v, int w) : v_(v), w_(w) {}
};

vector<edge> edges[n_max];
int distances[n_max][2];
	// distances[i][0] is the distance of i-th junction riding the cycyle
	// distances[i][1] is the distance of i-th junction carrying the cycle
bool visited[n_max][2];
	// visited[i][0] is true if i-th junction has already been reached riding the cycle
	// visited[i][1] is true if i-th junction has already been reached carrying the cycle

struct distance_comparator {
	bool operator () (const pair<int, int>& i, const pair<int, int>& j) const
	{
		if(distances[i.first][i.second] == distances[j.first][j.second])
			return i < j;
		else
			return distances[i.first][i.second] < distances[j.first][j.second];
	}
};

int dijkstra_shortest_path(int n)
{
	for (int i = 0 ; i < n; i++) {
		distances[i][0] = distances[i][1] = numeric_limits<int>::max();
		visited[i][0] = visited[i][1] = false;
	}
	distances[0][0] = 0;
	set <pair<int, int>, distance_comparator> pq; // priority queue
	pq.insert(make_pair(0, 0));
	while(!pq.empty()) {
		pair<int, int> u = *pq.begin();
		pq.erase(pq.begin());
		visited[u.first][u.second] = true;
		if (u.first == n - 1 && u.second == 0)
			break;
		int d = distances[u.first][u.second], second = 1 - u.second;
		const vector<edge>& e = edges[u.first];
		for (size_t i = 0; i < e.size(); i++)
			if (!visited[e[i].v_][second] && distances[e[i].v_][second] > d + e[i].w_) {
				pair<int, int> v = make_pair(e[i].v_, second);
				pq.erase(v); // remove v if it has already been in the queue
				distances[e[i].v_][second] = d + e[i].w_;
				pq.insert(v);
			}
	}
	return distances[n - 1][0];
}

int main()
{
	int n, r;
	for (int s = 1; cin >> n >> r; s++) {
		for (int i = 0; i < n; i++)
			edges[i].clear();
		while (r--) {
			int u, v, l;
			cin >> u >> v >> l;
			edges[u].push_back(edge(v, l));
			edges[v].push_back(edge(u, l));
		}
		int d = dijkstra_shortest_path(n);
		cout << "Set #" << s << endl;
		if (d != numeric_limits<int>::max())
			cout << d << endl;
		else
			cout << "?\n";
	}
	return 0;
}

