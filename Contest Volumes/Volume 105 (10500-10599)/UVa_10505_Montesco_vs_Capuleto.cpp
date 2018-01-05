
/*
	UVa 10505 - Montesco vs Capuleto

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10505_Montesco_vs_Capuleto.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int n_max = 200;
bool matrix[n_max + 1][n_max + 1];
int colors[n_max + 1];

int bfs(int n, int s)
{
	bool cycled = false;
	int cls[2] = {1, 0};
	queue<int> q;
	colors[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 1; v <= n; v++)
			if (matrix[u][v]) {
				if (colors[v] == -1) { // not visited yet
					colors[v] = 1 - colors[u];
					cls[colors[v]]++;
					q.push(v);
				}
				else if (colors[v] == colors[u])
					cycled = true;
			}
    }
	return (cycled) ? -1 : ((cls[0] > cls[1]) ? cls[0] : cls[1]);
}

int main()
{
	int m;
	cin >> m;
	while (m--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			colors[i] = -1;
			for (int j = 1; j <= n; j++)
				matrix[i][j] = false;
		}
		for (int i = 1; i <= n; i++) {
			int p;
			cin >> p;
			while (p--) {
				int j;
				cin >> j;
				if (j <= n)
					matrix[i][j] = matrix[j][i] = true;
			}
		}
		int invited = 0;
		for (int i = 1; i <= n; i++)
			if (colors[i] == -1) {
				int j = bfs(n, i);
				if (j != -1)
					invited += j;
			}
		cout << invited << endl;
	}
	return 0;
}

