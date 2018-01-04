
/*
	UVa 12324 - Philip J. Fry Problem

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12324_Philip_J_Fry_Problem.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100, ti_max = 1000, bi_max = 100, infinite = n_max * ti_max + 1;
int ti[n_max], bi[n_max];
int time[n_max][bi_max * bi_max + 1];
	// time[i][j] is the min. time of i-th trip with j dark matter spheres

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			scanf("%d %d", &ti[i], &bi[i]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= n * n; j++)
				time[i][j] = infinite;
		int b_max = bi[0];
		time[0][b_max] = ti[0];
#ifdef DEBUG
		printf("[0][%d]:%d\n", b_max, time[0][b_max]);
#endif
		for (int i = 1; i < n; i++) {
			int b = bi[i];
			for (int j = 0; j <= b_max; j++) {
				// time[i][j + b] = min(time[i - 1][j] + ti[i], time[i - 1][j + 1] + ti[i] / 2)
				int t = infinite;
				if (time[i - 1][j] < infinite)
					t = time[i - 1][j] + ti[i];
				if (j < b_max && time[i - 1][j + 1] < infinite)
					t = min(t, time[i - 1][j + 1] + ti[i] / 2);
				if (t < infinite)
					time[i][j + b] = t;
			}
			b_max += b;
#ifdef DEBUG
			for (int j = 0; j <= b_max; j++)
				if (time[i][j] < infinite)
					printf("[%d][%d]:%d ", i, j, time[i][j]);
			putchar('\n');
#endif
		}
		int t_min = infinite;
		for (int j = 0; j <= b_max; j++)
			t_min = min(t_min, time[n - 1][j]);
		printf("%d\n", t_min);
	}
	return 0;
}

