
/*
	UVa 12291 - Polyomino Composer

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12291_Polyomino_Composer.cpp
*/

#include <cstdio>

const int nm_max = 10;
char small[nm_max][nm_max + 1], large[nm_max][nm_max + 1];

bool polyomino(int n, int m, int ssi, int ssj)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (large[i][j] == '*') {
				for (int si = 0, li = i - ssi; si < m; si++, li++)
					for (int sj = 0, lj = j - ssj; sj < m; sj++, lj++)
						if (small[si][sj] == '*') {
							if (li < 0 || li >= n || lj < 0 || lj >= n || large[li][lj] != '*')
								return false;
							large[li][lj] = '.';
						}
				return true;
			}
	return false;
}

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			scanf("%s", large[i]);
		for (int i = 0; i < m; i++)
			scanf("%s", small[i]);
		int ssi = -1, ssj;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < m; j++)
				if (small[i][j] == '*') {
					ssi = i, ssj = j;
					break;
				}
			if (ssi != -1)
				break;
		}
		int possible = (polyomino(n, m, ssi, ssj) && polyomino(n, m, ssi, ssj)) ? 1 : 0;
		if (possible) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					if (large[i][j] == '*') {
						possible = 0;
						break;
					}
				if (!possible)
					break;
			}
		}
		printf("%d\n", possible);
	}
	return 0;
}

