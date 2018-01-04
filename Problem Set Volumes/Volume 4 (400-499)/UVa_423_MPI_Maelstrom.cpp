
/*
	UVa 423 - MPI Maelstrom

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_423_MPI_Maelstrom.cpp

	from 1996 ACM East Central Region Programming Contest Problem 5
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1996/solutions/index.html)
*/

#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>
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
	int n;
#ifdef ONLINE_JUDGE
	cin >> n;
#else
	while (cin >> n) {
#endif
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = numeric_limits<int>::max();
		for (int i = 1; i < n; i++)
			for (int j = 0; j < i; j++) {
				string s;
				cin >> s;
				if (s != "x")
					matrix[i][j] = matrix[j][i] = atoi(s.c_str());
			}
		floyd_warshall(n);
		int min_time = numeric_limits<int>::min();
		for (int i = 1; i < n; i++)
			min_time = max(min_time, matrix[0][i]);
		cout << min_time << endl;
#ifndef ONLINE_JUDGE
	}
#endif
	return 0;
}

