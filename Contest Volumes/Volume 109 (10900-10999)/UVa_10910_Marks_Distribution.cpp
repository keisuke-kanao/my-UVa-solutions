
/*
	UVa 10910 - Marks Distribution

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10910_Marks_Distribution.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 70, p_max = 70, t_max = 70;
int nr_ways[n_max + 1][t_max + 1];
	// nr_ways[i][j] is the number of ways in which j marks are distributed among i subjects.

int main()
{
	for (int i = 1; i <= n_max; i++)
		nr_ways[i][0] = 1;
	for (int j = 0; j <= t_max; j++)
		nr_ways[1][j] = 1;
	for (int i = 2; i <= n_max; i++)
		for (int j = 1; j <= t_max; j++) {
			nr_ways[i][j] = 0;
			for (int k = 0; k <= j; k++)
				nr_ways[i][j] += nr_ways[i - 1][k];
		}

	int k;
	cin >> k;
	while (k--) {
		int n, t, p;
		cin >> n >> t >> p;
		int m = t - n * p;
		cout << nr_ways[n][m] << endl;
	}
	return 0;
}

