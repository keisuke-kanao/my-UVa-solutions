
/*
	UVa 10459 - The Tree Root

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10459_The_Tree_Root.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int bfs(int n, int s, const vector< vector<int> >& edges, vector<int>& distances, vector<int>& prevs)
{
	for (int i = 0; i < n; i++)
		distances[i] = prevs[i] = -1;
	queue<int> q;
	distances[s] = 0;
	int furthest = s, d = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (distances[u] > d) {
			furthest = u;
			d = distances[u];
		}
		const vector<int>& es = edges[u];
		for (size_t j = 0, je = es.size(); j < je; j++) {
			int v = es[j];
			if (distances[v] == -1) {
				distances[v] = distances[u] + 1;
				prevs[v] = u;
				q.push(v);
			}
		}
	}
	return furthest;
}

int main()
{
	int N;
	while (cin >> N) {
		vector< vector<int> > edges(N + 1);
		for (int i = 1; i <= N; i++) {
			int k;
			cin >> k;
			while (k--) {
				int j;
				cin >> j;
				edges[i].push_back(j);
			}
		}
		vector<int> distances(N + 1), prevs(N + 1);
/*
		do DFS/BFS from any node s to find the furthest vertex u, 
		then do DFS/BFS one more time from vertex u to get the true furthest vertex v from u.
		The length of the unique path along u to v is the diameter of the tree.
*/
		int u = bfs(N + 1, 1, edges, distances, prevs);
		int v = bfs(N + 1, u, edges, distances, prevs);
		int diameter = distances[v];
#ifdef DEBUG
		cout << "diameter = " << diameter << endl;
		for (int i = v; i != -1; i = prevs[i])
			cout << i << ':' << distances[i] << ' ';
		cout << endl;
#endif
		int best_0, best_1 = -1;
		vector<int> worsts;
		if (diameter % 2) { // odd
			for (int i = v; ; i = prevs[i]) {
				if (distances[i] == (diameter + 1) / 2)
					best_1 = i;
				else if (distances[i] == diameter / 2) {
					best_0 = i;
					break;
				}
			}
			if (best_0 > best_1)
				swap(best_0, best_1);
		}
		else { // even
			for (int i = v; ; i = prevs[i])
				if (distances[i] == diameter / 2) {
					best_0 = i;
					break;
				}
		}
		v = bfs(N + 1, best_0, edges, distances, prevs);
		for (int i = 1; i <= N; i++)
			if (distances[i] == distances[v])
				worsts.push_back(i);
		if (best_1 != -1) {
			v = bfs(N + 1, best_1, edges, distances, prevs);
			for (int i = 1; i <= N; i++)
				if (distances[i] == distances[v])
					worsts.push_back(i);
		}
		sort(worsts.begin(), worsts.end());
		cout << "Best Roots  : " << best_0;
		if (best_1 != -1)
			cout << ' ' << best_1;
		cout << "\nWorst Roots :";
		for (size_t i = 0, e = worsts.size(); i < e; i++)
			cout << ' ' << worsts[i];
		cout << endl;
	}
	return 0;
}

