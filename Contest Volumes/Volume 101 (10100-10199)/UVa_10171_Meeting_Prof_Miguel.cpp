
/*
	UVa 10171 - Meeting Prof. Miguel...

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10171_Meeting_Prof_Miguel.cpp
*/

/*
	Generate two graphs, one is for people whose age is less than thirty, 
	and the other is for for people aged 30 or more.

	Apply Flyod-Warshall's all pairs shortest paths algorithm for the graphs.
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 'Z' - 'A' + 1;
const int cost_max = n_max * 500 + 1;

void floyd_warshall(int n, int matrix[n_max][n_max])
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}

int main()
{
	int matrix_for_young[n_max][n_max], matrix_for_rest[n_max][n_max];
	while (true) {
		int s;
		cin >> s;
		if (!s)
			break;
		for (int i = 0; i < n_max; i++)
			for (int j = 0; j < n_max; j++)
				matrix_for_young[i][j] = matrix_for_rest[i][j] = cost_max;
		int n_for_young = -1, n_for_rest = -1;
		while (s--) {
			char p, d, x, y;
			int c;
			cin >> p >> d >> x >> y >> c;
			int i = x - 'A', j = y - 'A';
			if (p == 'Y') {
				matrix_for_young[i][j] = min(matrix_for_young[i][j], c);
				if (d == 'B')
					matrix_for_young[j][i] = min(matrix_for_young[j][i], c);
				n_for_young = max(n_for_young, max(i, j));
			}
			else {
				matrix_for_rest[i][j] = min(matrix_for_rest[i][j], c);
				if (d == 'B')
					matrix_for_rest[j][i] = min(matrix_for_rest[j][i], c);
				n_for_rest = max(n_for_rest, max(i, j));
			}
		}
		char x, y;
		cin >> x >> y;
		int young = x - 'A', rest = y - 'A';
		matrix_for_young[young][young] = matrix_for_rest[rest][rest] = 0;
		n_for_young = max(n_for_young, young);
		n_for_rest = max(n_for_rest, rest);
		n_for_young++; n_for_rest++;
		floyd_warshall(n_for_young, matrix_for_young);
		floyd_warshall(n_for_rest, matrix_for_rest);
		int min_cost = cost_max * 2, min_i;
		for (int i = 0; i < n_max; i++)
			if (matrix_for_young[young][i] < cost_max && matrix_for_rest[rest][i] < cost_max) {
				int cost = matrix_for_young[young][i] + matrix_for_rest[rest][i];
				if (cost < min_cost) {
					min_cost = cost; min_i = i;
				}
			}
		if (min_cost < cost_max * 2) {
			cout << min_cost << ' ' << static_cast<char>('A' + min_i);
			for (int i = min_i + 1; i < n_max; i++)
				if (matrix_for_young[young][i] + matrix_for_rest[rest][i] == min_cost)
					cout << ' ' << static_cast<char>('A' + i);
			cout << endl;
		}
		else
			cout << "You will never meet.\n";
	}
	return 0;
}

