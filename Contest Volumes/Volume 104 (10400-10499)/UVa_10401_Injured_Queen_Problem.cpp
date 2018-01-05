
/*
	UVa 10401 - Injured Queen Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10401_Injured_Queen_Problem.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int n_max = 15;
long long nr_ways[n_max][n_max];

int main()
{
	char s[n_max + 1];
	while (scanf("%s", s) != EOF) {
		int i, j, k, n = strlen(s);
		for (i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				nr_ways[i][j] = 0;
		if(s[0] == '?') {
			for (j = 0; j < n; j++)
				nr_ways[0][j] = 1;
		}
		else {
			if (isdigit(s[0]))
				j = s[0] - '1';
			else
	            j = s[0] - 'F' + 14;
			nr_ways[0][j] = 1;
		}
		for (i = 1; i < n; i++) {
			if (s[i] == '?') {
				for (j = 0; j < n; j++) {
					for (k = 0; k < j - 1; k++)
						nr_ways[i][j] += nr_ways[i - 1][k];
					for (k = j + 2; k < n; k++)
						nr_ways[i][j] += nr_ways[i - 1][k];
				}
			}
			else {
				if (isdigit(s[i]))
					j = s[i] - '1';
				else
					j = s[i] - 'F' + 14;
				for (k = 0; k < j - 1; k++)
					nr_ways[i][j] += nr_ways[i - 1][k];
				for (k = j + 2; k < n; k++)
					nr_ways[i][j] += nr_ways[i - 1][k];
			}
		}
		long long nr = 0;
		for (j = 0; j < n; j++)
			nr += nr_ways[n - 1][j];
		printf("%lld\n", nr);
	}
	return 0;
}

