
/*
	UVa 459 - Graph Connectivity

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_459_Graph_Connectivity.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <cstring>
using namespace std;

const int nr_letters = 26;
bool matrix[nr_letters][nr_letters];
bool visited[nr_letters];

void bfs(int v, int n)
{
	queue<int> q;
	visited[v] = true;
	q.push(v);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (v = 0; v < n; v++)
			if (matrix[u][v] && !visited[v]) {
				visited[v] = true;
				q.push(v);
			}
	}
}

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int t;
	iss >> t;
	iss.clear();
	getline(cin, line); // skip a blank line
	while (t--) {
		getline(cin, line); // largest node name
		iss.str(line);
		char c;
		iss >> c;
		int n = c - 'A' + 1;
		iss.clear();
		memset(matrix, 0, sizeof(matrix));
		while (getline(cin, line) && line.length()) {
			iss.str(line);
			char cu, cv;
			iss >> cu >> cv;
			iss.clear();
			int u = cu - 'A', v = cv - 'A';
			matrix[u][v] = matrix[v][u] = true;
		}
		int nr_connected_components = 0;
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < n; i++)
			if (!visited[i]) {
				nr_connected_components++;
				bfs(i, n);
			}
		cout << nr_connected_components << endl;
		if (t)
			cout << endl;
	}
	return 0;
}

