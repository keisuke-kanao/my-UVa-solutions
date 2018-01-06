
/*
	UVa 10009 - All Roads Lead Where?

	To build using Visual Studio 2008:
		cl -EHsc UVa_10009_All_Roads_Lead_Where.cpp
*/

#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

const int nr_letters = 26;
bool matrix[nr_letters][nr_letters];
bool visited[nr_letters];
int parents[nr_letters];

void bfs(int n, int start, int end)
{
	queue<int> q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u == end)
			break;
		for (int i = 0; i < nr_letters; i++)
			if (matrix[u][i] && !visited[i]) {
				visited[i] = true;
				parents[i] = u;
				q.push(i);
			}
	}
}

void print_cities(int end)
{
	if (parents[end] != -1)
		print_cities(parents[end]);
	cout << static_cast<char>('A' + end);
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int m, n;
		cin >> m >> n;
		memset(matrix, 0, sizeof(matrix));
		for (int i = 0; i < m; i++) {
			string cu, cv;
			cin >> cu >> cv;
			int u = cu[0] - 'A', v = cv[0] - 'A';
			matrix[u][v] = matrix[v][u] = true;
		}
		for (int i = 0; i < n; i++) {
			string cu, cv;
			cin >> cu >> cv;
			int u = cu[0] - 'A', v = cv[0] - 'A';
			memset(visited, 0, sizeof(visited));
			memset(parents, -1, sizeof(parents));
			bfs(n, u, v);
			print_cities(v);
			cout << endl;
		}
		if (t)
			cout << endl;
	}
	return 0;
}

