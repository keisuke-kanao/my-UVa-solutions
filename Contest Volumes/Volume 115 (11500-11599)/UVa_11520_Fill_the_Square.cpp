
/*
	UVa 11520 - Fill the Square

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11520_Fill_the_Square.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int n_max = 10, nr_letters = 'Z' - 'A' + 1;
	char grid[n_max][n_max + 1];
	bool letters[nr_letters];
	int t;
	scanf("%d", &t);
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", grid[i]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (grid[i][j] == '.') {
					memset(letters, 0, sizeof(letters));
					if (i && grid[i - 1][j] != '.')
						letters[grid[i - 1][j] - 'A'] = true;
					if (i < n - 1 && grid[i + 1][j] != '.')
						letters[grid[i + 1][j] - 'A'] = true;
					if (j && grid[i][j - 1] != '.')
						letters[grid[i][j - 1] - 'A'] = true;
					if (j < n - 1 && grid[i][j + 1] != '.')
						letters[grid[i][j + 1] - 'A'] = true;
					for (int k = 0; ; k++)
						if (!letters[k]) {
							grid[i][j] = k + 'A'; break;
						}
				}
		printf("Case %d:\n", case_nr);
		for (int i = 0; i < n; i++)
			puts(grid[i]);
	}
	return 0;
}

