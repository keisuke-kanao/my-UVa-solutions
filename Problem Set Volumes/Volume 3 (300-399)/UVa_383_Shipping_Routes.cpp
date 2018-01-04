
/*
	UVa 383 - Shipping Routes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_383_Shipping_Routes.cpp

	from ACM Mid-Atlantic Regionals 1996
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidAtl/1996/index.html)

	A quite absurd problem!
	The only reason for wrong answers is whether an additional blank line should be appended or not.
	Even worse, for this additional blank line, the judge's answer is different from the original one.
*/

#include <iostream>
#include <string>
#include <map>
#include <queue>
using namespace std;

const int m_max = 30;
bool matrix[m_max][m_max];
bool visited[m_max];

int bfs(int n, int s, int d)
{
	for (int i = 0; i < n; i++)
		visited[i] = false;
	queue< pair<int, int> > q;
	visited[s] = true;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair<int, int> u = q.front(); q.pop();
		if (u.first == d)
			return u.second;
		for (int i = 0; i < n; i++)
			if (matrix[u.first][i] && !visited[i]) {
				visited[i] = true;
				q.push(make_pair(i, u.second + 1));
			}
	}
	return -1;
}

int main()
{
	int nr_ds;
	cin >> nr_ds;
	cout << "SHIPPING ROUTES OUTPUT\n\n";
	for (int ds = 1; ds <= nr_ds; ds++) {
		int m, n, p;
		cin >> m >> n >> p;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				matrix[i][j] = false;
		map<string, int> warehouses;
		for (int i = 0; i < m; i++) {
			string s;
			cin >> s;
			warehouses[s] = i;
		}
		for (int i = 0; i < n; i++) {
			string s, t;
			cin >> s >> t;
			int j = warehouses[s], k = warehouses[t];
			matrix[j][k] = matrix[k][j] = true;
		}
		cout << "DATA SET  " << ds << endl << endl;
		for (int i = 0; i < p; i++) {
			int size;
			string s, t;
			cin >> size >> s >> t;
			int j = warehouses[s], k = warehouses[t];
			int path = bfs(m, j, k);
			if (path != -1)
				cout << '$' << size * path * 100 << endl;
			else
				cout << "NO SHIPMENT POSSIBLE\n";
		}
		cout << endl;
	}
	cout << "END OF OUTPUT\n";
	return 0;
}


