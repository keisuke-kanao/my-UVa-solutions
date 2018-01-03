
/*
	UVa 1262 - Password

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1262_Password.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_rows = 6, nr_columns = 5;

char first[nr_columns][nr_rows], second[nr_columns][nr_rows], common[nr_columns][nr_rows];
int K, lengths[nr_columns];

void read_grid(char grid[nr_columns][nr_rows])
{
	for (int i = 0; i < nr_rows; i++) {
		char s[nr_columns + 1];
		scanf("%s", s);
		for (int j = 0; j < nr_columns; j++)
			grid[j][i] = s[j];
	}
	for (int i = 0; i < nr_columns; i++) {
		char (&g)[nr_rows] = grid[i];
		sort(g, g + nr_rows);
#ifdef DEBUG
		printf("%c%c%c%c%c%c\n", g[0], g[1], g[2], g[3], g[4], g[5]);
#endif
	}
}

bool password(int ci, char s[nr_columns + 1])
{
	if (ci == nr_columns) {
		K--;
		return !K;
	}
	else {
		for (int i = 0; i < lengths[ci]; i++) {
			s[ci] = common[ci][i];
			if (password(ci + 1, s))
				return true;
		}
		return false;
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &K);
		read_grid(first);
		read_grid(second);
		for (int i = 0; i < nr_columns; i++) {
			int l = 0;
			char (&f)[nr_rows] = first[i], (&s)[nr_rows] = second[i], (&c)[nr_rows] = common[i];
			for (int fi = 0, si = 0; fi < nr_rows && si < nr_rows; ) {
				char fc = f[fi], sc = s[si];
				if (fc == sc) {
					c[l++] = fc;
					for (fi++; fi < nr_rows && f[fi] == fc; fi++)
						;
					for (si++; si < nr_rows && s[si] == sc; si++)
						;
				}
				else if (fc < sc) {
					for (fi++; fi < nr_rows && f[fi] == fc; fi++)
						;
				}
				else {
					for (si++; si < nr_rows && s[si] == sc; si++)
						;
				}
			}
			lengths[i] = l;
		}
		int k = 1;
		for (int i = 0; i < nr_columns; i++)
			k *= lengths[i];
		if (k < K)
			puts("NO");
		else {
			char s[nr_columns + 1];
			s[nr_columns] = '\0';
			password(0, s);
			printf("%s\n", s);
		}
	}
	return 0;
}

