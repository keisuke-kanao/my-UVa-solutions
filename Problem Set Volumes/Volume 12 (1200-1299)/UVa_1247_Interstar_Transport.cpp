
/*
	UVa 1247 - Interstar Transport

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1247_Interstar_Transport.cpp
*/

#include <cstdio>

const int s_max = 26, cost_max = 100, infinite = (s_max + 1) * cost_max;
int dists[s_max][s_max], paths[s_max][s_max], nexts[s_max][s_max];

void floyd_warshall_with_path_reconstruction(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (dists[i][k] + dists[k][j] < dists[i][j] ||
					dists[i][k] + dists[k][j] == dists[i][j] && paths[i][k] + paths[k][j] < paths[i][j]) {
					dists[i][j] = dists[i][k] + dists[k][j];
					paths[i][j] = paths[i][k] + paths[k][j];
					nexts[i][j] = nexts[i][k];
				}
}

void print_path(int u, int v)
{
	putchar(u + 'A');
	while (u != v) {
		u = nexts[u][v];
		printf(" %c", u + 'A');
	}
	putchar('\n');
}

int main()
{
	for (int i = 0; i < s_max; i++)
		for (int j = 0; j < s_max; j++) {
			dists[i][j] = infinite;
			paths[i][j] = s_max + 1;
			nexts[i][j] = -1;
		}
	int s, p;
	scanf("%d %d", &s, &p);
	while (p--) {
		char ei[2], ej[2];
		int dij;
		scanf("%s %s %d", ei, ej, &dij);
		int u = ei[0] - 'A', v = ej[0] - 'A';
		dists[u][v] = dists[v][u] = dij;
		paths[u][v] = paths[v][u] = 1;
		nexts[u][v] = v; nexts[v][u] = u;
	}
	floyd_warshall_with_path_reconstruction(s_max);
	int n;
	scanf("%d", &n);
	while (n--) {
		char ek[2], em[2];
		scanf("%s %s", ek, em);
		print_path(ek[0] - 'A', em[0] - 'A');
	}
	return 0;
}

