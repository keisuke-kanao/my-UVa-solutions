
/*
	UVa 10443 - Rock

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10443_Rock.cpp

	from Waterloo ACM Programming Contest January 25, 2003 Problem E
  		(http://acm.student.cs.uwaterloo.ca/~acm00/030125/data/)
*/

#include <cstdio>

const int r_max = 100, c_max = 100;
char grids[2][r_max][c_max + 1];

char war(char ci, char cj)
{
/*
  P Q R S
P P - P S
Q - - - -
R P - R R
S S - R S
*/
	const char wars[4][4] = { // wars[ci][cj] is the result of war between (ci - 'P') and (cj - 'P')
		{'P', '\0', 'P', 'S'},
		{'\0', '\0', '\0', '\0'},
		{'P', '\0', 'R', 'R'},
		{'S', '\0', 'R', 'S'}
	};
	return wars[ci - 'P'][cj - 'P'];
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int r, c, n;
		scanf("%d %d %d", &r, &c, &n);
		for (int i = 0; i < r; i++)
			scanf("%s", grids[0][i]);
		for (int k = 1; k <= n; k++) {
			int ck = k % 2, pk = (k - 1) % 2;
			for (int i = 0; i < r ; i++)
				for (int j = 0; j < c; j++) {
					char cc, pc = grids[pk][i][j];
					if (i && (cc = war(pc, grids[pk][i - 1][j])) != pc ||
						i < r - 1 && (cc = war(pc, grids[pk][i + 1][j])) != pc ||
						j && (cc = war(pc, grids[pk][i][j - 1])) != pc ||
						j < c - 1 && (cc = war(pc, grids[pk][i][j + 1])) != pc)
						grids[ck][i][j] = cc;
					else
						grids[ck][i][j] = pc;
				}
		}
		for (int i = 0; i < r; i++) {
			grids[n % 2][i][c] = '\0';
			puts(grids[n % 2][i]);
		}
		if (t)
			putchar('\n');
	}
	return 0;
}

