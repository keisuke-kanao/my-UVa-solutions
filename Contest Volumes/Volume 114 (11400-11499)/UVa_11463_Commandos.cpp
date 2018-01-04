
/*
	UVa 11463 - Commandos

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11463_Commandos.cpp
*/

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

const int n_max = 100;
int matrix[n_max][n_max];

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (matrix[i][k] != numeric_limits<int>::max() && matrix[k][j] != numeric_limits<int>::max()) {
					int through_k = matrix[i][k] + matrix[k][j]; // distance through vertex k
 					if (through_k < matrix[i][j])
						matrix[i][j] = through_k;
				}
}

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n, r;
		cin >> n >> r;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = numeric_limits<int>::max();
		while (r--) {
			int u, v;
			cin >> u >> v;
			matrix[u][v] = matrix[v][u] = 1;
		}
		int s, d;
		cin >> s >> d;
		floyd_warshall(n);
		int min_t = 0;
		for (int i = 0; i < n; i++) {
			int t = (i != s) ? matrix[s][i] : 0;
			if (i != d)
				t += matrix[i][d];
			min_t = max(min_t, t);
		}
		cout << "Case " << case_nr << ": " << min_t << endl;
	}
	return 0;
}

