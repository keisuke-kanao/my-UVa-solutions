
/*
	UVa 10342 - Always Late

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10342_Always_Late.cpp
*/

#include <limits>
#include <cstdio>
using namespace std;

const int infinite = numeric_limits<int>::max();

const int n_max = 100;
int matrix[n_max][n_max], second_matrix[n_max][n_max];

struct edge {
	int u_, v_, w_;
} edges[n_max * n_max];

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			if (matrix[i][k] != infinite)
				for (int j = 0; j < n; j++)
					if (matrix[k][j] != infinite && matrix[i][k] + matrix[k][j] < matrix[i][j])
						matrix[i][j] = matrix[i][k] + matrix[k][j];
}

void all_pairs_second_shortest_paths(int e, int n)
{
	for (int k = 0; k < e; k++) {
		int u = edges[k].u_, v = edges[k].v_, w = edges[k].w_;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (matrix[i][u] != infinite && matrix[v][j] != infinite) {
					int nw = matrix[i][u] + w + matrix[v][j];
					if (nw > matrix[i][j] && nw < second_matrix[i][j])
						second_matrix[i][j] = nw;
				}
	}
}

int main()
{
	for (int sn = 1; ; sn++) {
		int n, r;
		if (scanf("%d %d", &n, &r) < 2)
			break;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				matrix[i][j] = (i != j) ? infinite : 0;
				second_matrix[i][j] = infinite;
			}
		for (int i = 0; i < r; i++) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			matrix[u][v] = matrix[v][u] = w;
			edges[i * 2].u_ = u, edges[i * 2].v_ = v, edges[i * 2].w_ = w;
			edges[i * 2 + 1].u_ = v, edges[i * 2 + 1].v_ = u, edges[i * 2 + 1].w_ = w;
		}
		floyd_warshall(n);
		all_pairs_second_shortest_paths(r * 2, n);
		int q;
		scanf("%d", &q);
		printf("Set #%d\n", sn);
		while (q--) {
			int u, v;
			scanf("%d %d", &u, &v);
			if (second_matrix[u][v] != infinite)
				printf("%d\n", second_matrix[u][v]);
			else
				puts("?");
		}
	}
	return 0;
}

