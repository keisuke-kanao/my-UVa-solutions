
/*
	UVa 11550 - Demanding Dilemma

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11550_Demanding_Dilemma.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 8, m_max = 28;
	int t, matrix[n_max][m_max];
	bool incidence_matrix[n_max][n_max];
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> matrix[i][j];
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				incidence_matrix[i][j] = false;
		bool yes = true;
		for (int j = 0; j < m; j++) {
			int u = -1, v = -1;
			for (int i = 0; i < n; i++)
				if (matrix[i][j]) {
					if (u == -1)
						u = i;
					else if (v == -1)
						v = i;
					else {
						yes = false; break;
					}
				}
			if (u == - 1 || v == -1 || !yes || incidence_matrix[u][v]) {
				yes = false; break;
			}
			else
				incidence_matrix[u][v] = true;
		}
		cout << ((yes) ? "Yes\n" : "No\n");
	}
	return 0;
}

