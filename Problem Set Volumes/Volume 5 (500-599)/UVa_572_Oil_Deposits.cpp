
/*
	UVa 572 - Oil Deposits

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_572_Oil_Deposits.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

void set_adjacencies(int m, int n, int i, int j, int k,
	const vector< vector<int> >& grids, vector< vector<int> >& matrix)
{
	int l;
	if (i) {
		const vector<int>& g = grids[i - 1];
		if ((l = g[j]) != -1) // upper
			matrix[k][l] = matrix[l][k] = 1;
		if (j && (l = g[j - 1]) != -1) // upper left
			matrix[k][l] = matrix[l][k] = 1;
		if (j < n - 1 && (l = g[j + 1]) != -1) // upper right
			matrix[k][l] = matrix[l][k] = 1;
	}
	const vector<int>& g = grids[i];
	if (j && (l = g[j - 1]) != -1) // left
		matrix[k][l] = matrix[l][k] = 1;
	if (j < n - 1 && (l = g[j + 1]) != -1) // right
		matrix[k][l] = matrix[l][k] = 1;
	if (i < m - 1) {
		const vector<int>& g = grids[i + 1];
		if ((l = g[j]) != -1) // lower
			matrix[k][l] = matrix[l][k] = 1;
		if (j && (l = g[j - 1]) != -1) // lower left
			matrix[k][l] = matrix[l][k] = 1;
		if (j < n - 1 && (l = g[j + 1]) != -1) // lower right
			matrix[k][l] = matrix[l][k] = 1;
	}
}

void dfs(int i, int n, vector<bool>& visited, const vector< vector<int> >& matrix)
{
	visited[i] = true;
	const vector<int>& m = matrix[i];
	for (int j = 0; j < n; j++)
		if (m[j] && !visited[j])
			dfs(j, n, visited, matrix);
}

int main()
{
	while (true) {
		int m, n;
		cin >> m >> n;
		if (!m)
			break;
		vector< vector<int> > grids(m, vector<int>(n, -1));
		int nr_pockets = 0;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				char c;
				cin >> c;
				if (c == '@')
					grids[i][j] = nr_pockets++;
			}
		vector< vector<int> > matrix(nr_pockets, vector<int>(nr_pockets, 0)); // adjacent matrix
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				int k = grids[i][j];
				if (k != -1)
					set_adjacencies(m, n, i, j, k, grids, matrix);
			}
		int nr_connected_components = 0;
		vector<bool> visited(nr_pockets, false);
		for (int i = 0; i < nr_pockets; i++)
			if (!visited[i]) {
				dfs(i, nr_pockets, visited, matrix); // do a depth-first search
				nr_connected_components++;
			}
		cout << nr_connected_components << endl;
	}
	return 0;
}

