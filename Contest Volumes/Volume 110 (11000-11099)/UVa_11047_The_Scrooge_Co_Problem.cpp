
/*
	UVa 11047 - The Scrooge Co Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11047_The_Scrooge_Co_Problem.cpp
*/

#include <cstdio>
#include <cstring>
#include <limits>
using namespace std;

const int n_max = 99, nr_chars_max = 31;

char names[n_max][nr_chars_max + 1];
int dists[n_max][n_max], nexts[n_max][n_max];

int get_index(int n, const char* name)
{
	for (int i = 0; i < n; i++)
		if (!strcmp(name, names[i]))
			return i;
	return -1;
}

void floyd_warshall_with_path_reconstruction(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			if (dists[i][k] != numeric_limits<int>::max())
				for (int j = 0; j < n; j++)
					if (dists[k][j] != numeric_limits<int>::max() &&
						dists[i][k] + dists[k][j] < dists[i][j]) {
						dists[i][j] = dists[i][k] + dists[k][j];
						nexts[i][j] = nexts[i][k];
					}
}

void print_path(int u, int v)
{
	printf("Path:%s", names[u]);
	do {
		u = nexts[u][v];
		printf(" %s", names[u]);
	} while (u != v);
	putchar('\n');
}

int main()
{
	int C;
	scanf("%d", &C);
	while (C--) {
		int P;
		scanf("%d", &P);
		for (int i = 0; i < P; i++)
			scanf("%s", names[i]);
		for (int i = 0; i < P; i++)
			for (int j = 0; j < P; j++) {
				int C;
				scanf("%d", &C);
				dists[i][j] = (C >= 0) ? C : numeric_limits<int>::max();
				nexts[i][j] = j;
			}
		floyd_warshall_with_path_reconstruction(P);
		int R;
		scanf("%d", &R);
		while (R--) {
			char employee[nr_chars_max + 1], start[nr_chars_max + 1], end[nr_chars_max + 1];
			scanf("%s %s %s", employee, start, end);
			int s = get_index(P, start), e = get_index(P, end);
			if (dists[s][e] != numeric_limits<int>::max()) {
				printf("Mr %s to go from %s to %s, you will receive %d euros\n", employee, start, end, dists[s][e]);
				print_path(s, e);
			}
			else
				printf("Sorry Mr %s you can not go from %s to %s\n", employee, start, end);
		}
	}
	return 0;
}

