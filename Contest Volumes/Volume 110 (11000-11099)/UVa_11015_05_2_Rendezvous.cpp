
/*
	UVa 11015 - 05-2 Rendezvous

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11015_05_2_Rendezvous.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int n_max = 22, k_max = 1000;
const int cost_max = n_max * k_max + 1;
int matrix[n_max][n_max];

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n, m;
		cin >> n >> m;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = (i == j) ? 0 : cost_max;
		vector<string> members(n);
		for (int i = 0; i < n; i++)
			cin >> members[i];
		while (m--) {
			int i, j, k;
			cin >> i >> j >> k;
			i--; j--;
			matrix[i][j] = matrix[j][i] = k;
		}
		floyd_warshall(n);
		int min_i = 0, min_d = cost_max;
		for (int i = 0; i < n; i++) {
			int d = 0;
			for (int j = 0; j < n; j++)
				d += matrix[i][j];
			if (d < min_d) {
				min_i = i; min_d = d;
			}
		}
		cout << "Case #" << case_nr << " : " << members[min_i] << endl;
	}
	return 0;
}

