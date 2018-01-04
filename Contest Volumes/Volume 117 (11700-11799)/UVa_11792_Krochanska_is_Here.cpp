
/*
	UVa 11792 - Krochanska is Here!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11792_Krochanska_is_Here.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

int bfs(int n, int ss, const vector<int>& stations, const vector< vector<int> >& adjacency_list)
{
	int s = 0;
	vector<bool> visited(n, false);
	queue< pair<int, int> > q;
	visited[ss] = true;
	q.push(make_pair(ss, 0));
	while (!q.empty()) {
		pair<int, int> u = q.front(); q.pop();
		if (stations[u.first] > 1)
			s += u.second;
		const vector<int>& al = adjacency_list[u.first];
		for (size_t i = 0, e = al.size(); i < e; i++) {
			int v = al[i];
			if (!visited[v]) {
				visited[v] = true;
				q.push(make_pair(v, u.second + 1));
			}
		}
	}
	return s;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int N, S;
		cin >> N >> S;
		vector<int> stations(N + 1, 0);
		vector< vector<int> > adjacency_list(N + 1);
		while (S--) {
			int u = - 1, v;
			while (true) {
				cin >> v;
				if (!v)
					break;
				stations[v]++;
				if (u != -1) {
					adjacency_list[u].push_back(v);
					adjacency_list[v].push_back(u);
				}
				u = v;
			}
		}
		int min_average = numeric_limits<int>::max(), min_average_i;
		for (int i = 1; i <= N; i++)
			if (stations[i] > 1) {
				int average = bfs(N + 1, i, stations, adjacency_list);
				if (average < min_average) {
					min_average = average;
					min_average_i = i;
				}
			}
		cout << "Krochanska is in: " << min_average_i << endl;
	}
	return 0;
}

