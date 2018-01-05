
/*
	UVa 11360 - Have Fun with Matrices

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11360_Have_Fun_with_Matrices.cpp
*/

#include <cstdio>

int main()
{
	const int n_max = 10;
	char matrices[2][n_max][n_max];
	char s[16];
	int t;
	scanf("%d", &t);
	getchar();
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n;
		scanf("%d", &n);
		getchar();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%c", &matrices[0][i][j]);
			getchar();
		}
		int m;
		scanf("%d", &m);
		getchar();
		int k = 0, ck, nk, a, b;
		char c;
		while (m--) {
			ck = k % 2;
			scanf("%s", s);
			if (s[0] == 'r') { // row
				scanf("%d %d", &a, &b);
				a--; b--;
				for (int j = 0; j < n; j++) {
					c = matrices[ck][a][j]; matrices[ck][a][j] = matrices[ck][b][j]; matrices[ck][b][j] = c;
				}
			}
			else if (s[0] == 'c') { // col
				scanf("%d %d", &a, &b);
				a--; b--;
				for (int i = 0; i < n; i++) {
					c = matrices[ck][i][a]; matrices[ck][i][a] = matrices[ck][i][b]; matrices[ck][i][b] = c;
				}
			}
			else if (s[0] == 'i') { // inc
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						if (++matrices[ck][i][j] > '9')
							matrices[ck][i][j] = '0';
			}
			else if (s[0] == 'd') { // dec
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						if (--matrices[ck][i][j] < '0')
							matrices[ck][i][j] ='9';
			}
			else { // transpose
				nk = (k + 1) % 2;
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						matrices[nk][i][j] = matrices[ck][j][i];
				k++;
			}
			getchar();
		}
		printf("Case #%d\n", case_nr);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				putchar(matrices[k % 2][i][j]);
			putchar('\n');
		}
		putchar('\n');
	}
	return 0;
}

