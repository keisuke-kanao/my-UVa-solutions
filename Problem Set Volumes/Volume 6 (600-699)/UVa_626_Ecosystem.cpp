
/*
	UVa 626 - Ecosystem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_626_Ecosystem.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 100;

int matrix[n_max + 1][n_max + 1], cycles[3 + 1];

void find_cycle(int u, int n, int ci, int& nc)
{
	cycles[ci] = u;
	if (ci == 1) {
		for (int v = 1; v <= n; v++)
			if (matrix[u][v])
				find_cycle(v, n, ci + 1, nc);
	}
	else if (ci == 2) {
		for (int v = 1; v <= n; v++)
			if (matrix[u][v]) {
				if (cycles[1] < cycles[2] && cycles[2] < v || cycles[1] > cycles[2] && cycles[2] > v)
					find_cycle(v, n, ci + 1, nc);
			}
	}
	else {
		if (matrix[u][cycles[1]]) {
			nc++;
			cout << cycles[1] << ' ' << cycles[2] << ' ' << cycles[3] << endl;
		}
	}
}

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> matrix[i][j];
		int nc = 0;
		for (int i = 1; i <= n; i++)
			find_cycle(i, n, 1, nc);
		cout << "total:" << nc << endl << endl;
	}
	return 0;
}

