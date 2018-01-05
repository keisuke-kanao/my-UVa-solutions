
/*
	UVa 11055 - Homogeneous squares

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11055_Homogeneous_squares.cpp
*/

#include <cstdio>

/*
a square is homogeneous if cell[i][j] - cell[i][j-1] == cell[i-1][j] - cell[i-1][j-1] for each 0 < i < n, 0< j < n.
*/

const int n_max = 1000;
int diffs[n_max];

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		bool homogeneous = true;
		int i, j, k, pk;
		for (j = 0; j < n; j++, pk = k) {
			scanf("%d", &k);
			if (j)
				diffs[j] = k - pk;
		}
		for (i = 1; i < n; i++) {
			for (j = 0; j < n && homogeneous; j++, pk = k) {
				scanf("%d", &k);
				if (j && k - pk != diffs[j])
					homogeneous = false;
			}
			for ( ; j < n; j++)
				scanf("%*d");
		}
		puts((homogeneous) ? "homogeneous" : "not homogeneous");
	}
	return 0;
}

