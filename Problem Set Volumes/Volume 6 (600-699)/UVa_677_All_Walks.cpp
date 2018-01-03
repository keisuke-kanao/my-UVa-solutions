
/*
	UVa 677 - All Walks of length "n" from the first node

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_677_All_Walks.cpp
*/

#include <cstdio>

const int n_max = 10;
bool matrix[n_max][n_max];
bool visited[n_max];
int paths[n_max];

bool dfs(int n, int ni, int l, int li)
{
	bool result = false;
	paths[li] = ni;
	if (li == l) {
		result = true;
		putchar('(');
		for (int i = 0; i <= l; i++)
			printf("%d%c", paths[i] + 1, ((i < l) ? ',' : ')'));
		putchar('\n');
	}
	else {
		for (int i = 0; i < n; i++)
			if (matrix[ni][i] && !visited[i]) {
				visited[i] = true;
				if (dfs(n, i, l, li + 1))
					result = true;
				visited[i] = false;
			}
	}
	return result;
}

int main()
{
	while (true) {
		int n, l;
		scanf("%d %d", &n, &l);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int zero_or_one;
				scanf("%d", &zero_or_one);
				matrix[i][j] = zero_or_one;
			}
			visited[i] = false;
		}
		visited[0] = true;
		if (!dfs(n, 0, l, 0))
				printf("no walk of length %d\n", l);
		int separator;
		if (scanf("%*d", &separator) == EOF)
			break;
		else
			putchar('\n');
	}
	return 0;
}

