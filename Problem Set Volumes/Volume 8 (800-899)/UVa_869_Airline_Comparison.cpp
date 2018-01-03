
/*
	UVa 869 - Airline Comparison

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_869_Airline_Comparison.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_chars_max = 128;
int vertices[nr_chars_max];
int matrix[nr_chars_max][nr_chars_max]; // adjacency matrix

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < nr_chars_max; i++) {
			vertices[i] = -1;
			for (int j = 0; j < nr_chars_max; j++)
				matrix[i][j] = nr_chars_max;
		}
		int n, m, nr_vertices = 0;
		cin >> n;
		while (n--) {
			char u, v;
			cin >> u >> v;
			if (vertices[u] == -1)
				vertices[u] = nr_vertices++;
			if (vertices[v] == -1)
				vertices[v] = nr_vertices++;
			matrix[vertices[u]][vertices[v]] = matrix[vertices[v]][vertices[u]] = 1;
		}
		floyd_warshall(nr_vertices);
		cin >> m;
		bool equivalent = true;
		while (m--) {
			char u, v;
			cin >> u >> v;
			if (equivalent) {
				if (vertices[u] == -1 || vertices[v] == -1 || 
					matrix[vertices[u]][vertices[v]] == nr_chars_max)
					equivalent = false;
			}
		}
		cout << ((equivalent) ? "YES\n" : "NO\n");
		if (t)
			cout << endl;
	}
	return 0;
}

