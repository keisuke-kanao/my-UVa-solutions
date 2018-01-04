
/*
	UVa 125 - Numbering Paths

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_125_Numbering_Paths.cpp

	from Duke Internet Programming Contest 1993
		(http://contest.mff.cuni.cz/old/archive/duke1993/)

	Note that the judges's solution (h.c, h.out) is WRONG.
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 30;
int nr_paths[n_max][n_max];
bool visited[n_max];

void number_paths(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				nr_paths[i][j] += nr_paths[i][k] * nr_paths[k][j];
	for (int k = 0; k < n; k ++)
		if (nr_paths[k][k]) { // k is in a cycle
			for (int i = 0; i < n; i ++)
				for (int j = 0; j < n; j ++)
					if (nr_paths[i][k] && nr_paths[k][j]) // there is a path from i to j that passes k
						nr_paths[i][j] = -1;
		}
}

int main()
{
	for (int city = 0; ; city++) {
		int nr_streets;
		if (!(cin >> nr_streets))
			break;
		for (int i = 0; i < n_max; i++)
			for (int j = 0; j < n_max; j++)
				nr_paths[i][j] = 0;
		int n = 0;
		while (nr_streets--) {
			int j, k;
			cin >> j >> k;
			nr_paths[j][k] = 1;
			n = max(n, max(j, k));
		}
		n++;
		number_paths(n);
		cout << "matrix for city " << city << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j)
					cout << ' ';
				cout << nr_paths[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}

