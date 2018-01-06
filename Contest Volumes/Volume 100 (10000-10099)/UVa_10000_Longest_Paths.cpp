
/*
	UVa 10000 - Longest Paths

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10000_Longest_Paths.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 100;
int matrix[n_max + 1][n_max + 1]; // adjacency matrix

void floyd_warshall(int n)
{
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}

int main()
{
	for (int c = 1; ; c++) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				matrix[i][j] = n + 1;
		int s;
		cin >> s;
		while (true) {
			int p, q;
			cin >> p >> q;
			if (!p && !q)
				break;
			matrix[p][q] = -1;
		}
		floyd_warshall(n);
		int e = s, min_length = 0;
		for (int i = 1; i <= n; i++)
			if (matrix[s][i] < min_length) {
				e = i; min_length = matrix[s][i];
			}
		cout << "Case " << c << ": The longest path from " << s << " has length " << -min_length <<
			", finishing at " << e << ".\n\n";
	}
	return 0;
}

