
/*
	UVa 10593 - Kites

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10593_Kites.cpp

	This is an accepted solution.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 500;
char sheet[n_max + 1][n_max + 2];
int n, nrs[n_max + 2][n_max + 2];
	// for squares, nrs[i][j] is the side length of of a square whose bottom right corner is sheet[i][j]
	// for diamonds, nr[i][j] is the side length of a diamond whose bottom corner is sheet[i][j]

int main ()
{
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; i++)
			scanf("%s", &sheet[i][1]);
		int nr_squares = 0, nr_diamonds = 0;
		memset(nrs, 0, sizeof(nrs));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (sheet[i][j] == 'x') {
					int nr = min(nrs[i - 1][j], nrs[i][j - 1]);
					// see if there is a lager square
					if (sheet[i - nr][j - nr] == 'x')
						nr++;
					if ((nrs[i][j] = nr) > 1)
						nr_squares += nr - 1;
				}
#ifdef DEBUG
		printf("squares: %d\n", nr_squares);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				printf("[%d][%d]:%d%c", i, j, nrs[i][j], ((j < n) ? ' ' : '\n'));
#endif
		memset(nrs, 0, sizeof(nrs));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
            	if (sheet[i][j] == 'x') {
					// see if there is a lower half of diamond
					int nr = min(nrs[i - 1][j - 1], nrs[i - 1][j + 1]);
    	            if (nr == 0 || sheet[i - 1][j] != 'x')
						nr = 1;
					// see if there is a upper half of diamond
					else if (sheet[i - nr * 2][j] == 'x' && sheet[i - nr * 2 + 1][j] == 'x')
						nr++;
					if ((nrs[i][j] = nr) > 1)
						nr_diamonds += nr - 1;
				}
#ifdef DEBUG
		printf("diamonds: %d\n", nr_diamonds);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				printf("[%d][%d]:%d%c", i, j, nrs[i][j], ((j < n) ? ' ' : '\n'));
#endif
		printf("%d\n", nr_squares + nr_diamonds);
	}
    return 0;
}

