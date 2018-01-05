
/*
	UVa 10793 - The Orc Attack

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10793_The_Orc_Attack.cpp
*/

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

const int l_max = 100;
int matrix[l_max + 1][l_max + 1];

int main()
{
	int t;
	cin >> t;
	for (int m = 1; m <= t; m++) {
		int l, d;
		cin >> l >> d;
		for (int i = 1; i <= l; i++)
			for (int j = 1; j <= l; j++)
				matrix[i][j] = numeric_limits<int>::max();
		while (d--) {
			int u, v, c;
			cin >> u >> v >> c;
			matrix[u][v] = matrix[v][u] = min(c, matrix[u][v]);
		}
		// apply Floyd-Warshall all-pairs shortest path algorithm
		for (int k = 1; k <= l; k++)
			for (int i = 1; i <= l; i++)
				for (int j = 1; j <= l; j++)
					if (matrix[i][k] != numeric_limits<int>::max() && matrix[k][j] != numeric_limits<int>::max()) {
						int through_k = matrix[i][k] + matrix[k][j];
 						if (through_k < matrix[i][j])
							matrix[i][j] = through_k;
					}
		int max_d = numeric_limits<int>::max();
		for (int i = 6; i <= l; i++) {
			int j;
			for (j = 1; j < 5; j++)
				if (matrix[i][j] != matrix[i][j + 1])
					break;
			if (j == 5 && matrix[i][1] != numeric_limits<int>::max()) {
				// i is equidistant from the five unit producing buildings
				int max_d_i = matrix[i][1];
				for (j = 6; j <= l; j++)
					if (i != j)
						max_d_i = max(max_d_i, matrix[i][j]);
				if (max_d_i != numeric_limits<int>::max()) // i is reachable from every other locations
					max_d = min(max_d, max_d_i);
			}
		}
		cout << "Map " << m << ": " << ((max_d != numeric_limits<int>::max()) ? max_d : -1) << endl;
	}
	return 0;
}

