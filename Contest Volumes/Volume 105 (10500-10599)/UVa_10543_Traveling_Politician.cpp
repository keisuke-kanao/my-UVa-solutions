
/*
	UVa 10543 - Traveling Politician

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10543_Traveling_Politician.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

const int n_max = 50, k_max = 20;
vector<int> routes[n_max];
bool cities[k_max + 1][n_max]; // cities[k][i] is true if there can be a k-th speech at i-th city

int main()
{
	while (true) {
		int n, m, k, k_min;
		cin >> n >> m >> k_min;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			routes[i].clear();
		while (m--) {
			int u, v;
			cin >> u >> v;
			if (u != v)
				routes[u].push_back(v);
		}
		for (int i = 0; i <= k_max; i++)
			for (int j = 0; j < n; j++)
				cities[i][j] = false;
		cities[1][0] = true;
		bool done = false;
		for (k = 2; k <= k_max; k++) {
			bool speeches = false;
			for (int i = 0; i < n; i++) {
				if (cities[k - 1][i]) {
					speeches = true;
					const vector<int>& rs = routes[i];
					for (size_t j = 0, je = rs.size(); j < je; j++) {
						cities[k][rs[j]] = true;
						if (k >= k_min && rs[j] == n - 1) {
							done = true; break;
						}
					}
				}
				if (done)
					break;
			}
			if (done || !speeches)
				break;
		}
		if (done)
			cout << k << endl;
		else
			cout << "LOSER\n";
	}
	return 0;
}

