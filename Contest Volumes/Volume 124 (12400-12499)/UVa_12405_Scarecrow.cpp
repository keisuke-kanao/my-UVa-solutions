
/*
	UVa 12405 - Scarecrow

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12405_Scarecrow.cpp
*/

#include <cstdio>

int main()
{
	const int n_max = 100;
	char field[n_max];
	int t;
	scanf("%d", &t);
	for (int ti = 1; ti <= t; ti++) {
		int n;
		scanf("%d", &n);
		scanf("%s", field);
		int nr_scarecrows = 0;
		for (int i = 0; i < n; ) {
			if (field[i] == '.') {
				i += 3;
				nr_scarecrows++;
			}
			else
				i++;
		}
		printf("Case %d: %d\n", ti, nr_scarecrows);
	}
	return 0;
}

