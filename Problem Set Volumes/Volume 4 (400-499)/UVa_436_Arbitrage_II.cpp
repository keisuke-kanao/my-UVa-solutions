
/*
	UVa 436 - Arbitrage (II)

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_436_Arbitrage_II.cpp

	from University of Ulm Local Contest 1996
		(http://www.informatik.uni-ulm.de/acm/Locals/1996/)
*/

#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <cmath>
using namespace std;

const int n_max = 30;
double matrix[n_max][n_max];

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (matrix[i][k] != numeric_limits<double>::max() && matrix[k][j] != numeric_limits<double>::max()) {
					double through_k = matrix[i][k] + matrix[k][j]; // distance through vertex k
 					if (through_k < matrix[i][j])
						matrix[i][j] = through_k;
				}
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		 map<string, int> currencies;
		for (int i = 0; i < n; i++) {
			string c;
			cin >> c;
			currencies[c] = i;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = (i == j) ? 0.0 : numeric_limits<double>::max();
		int m;
		cin >> m;
		for (int i = 0; i < m; i++) {
			string ci, cj;
			double rij;
			cin >> ci >> rij >> cj;
			matrix[currencies[ci]][currencies[cj]] = -log(rij);
		}
		floyd_warshall(n);
		bool yes = false;
		for (int i = 0; i < n; i++) {
			double profit = 1.0 / exp(matrix[i][i]);
			if (profit > 1.0) {
				yes = true; break;
			}
		}
		cout << "Case " << case_nr << ((yes) ? ": Yes\n" : ": No\n");
	}
	return 0;
}

