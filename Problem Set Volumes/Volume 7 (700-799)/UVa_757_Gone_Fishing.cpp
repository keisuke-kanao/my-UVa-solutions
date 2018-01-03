
/*
	UVa 757 - Gone Fishing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_757_Gone_Fishing.cpp
*/

#include <cstdio>

const int n_max = 25, h_max = 16, interval = 5, nr_intervals_max = h_max * 60 / interval;

int fi[n_max], di[n_max], ti[n_max];
int caught[n_max][nr_intervals_max + 1];
	// caught[i][j] is the number of fishes caught at the i-th lake with j intervals spent
int from[n_max][nr_intervals_max + 1];

void print_intervals(int i, int j)
{
	if (!i)
		printf("%d", j * interval);
	else {
		print_intervals(i - 1, from[i][j]);
		printf(", %d", (j - from[i][j]) * interval);
	}
}

int main()
{
	bool printed = false;
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		if (printed)
			putchar('\n');
		else
			printed = true;
		int h;
		scanf("%d", &h);
		int nr_intervals = h * 60 / interval;
		for (int i = 0; i < n; i++)
			scanf("%d", &fi[i]);
		for (int i = 0; i < n; i++)
			scanf("%d", &di[i]);
		for (int i = 0; i < n - 1; i++)
			scanf("%d", &ti[i]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < nr_intervals; j++)
				caught[i][j] = from[i][j] = 0;
		for (int j = 1, f = fi[0], c = f; j <= nr_intervals; j++) {
			caught[0][j] = c;
			if ((f -= di[0]) > 0)
				c += f;
		}
		int max_i = 0, max_j = nr_intervals;
		nr_intervals -= ti[0];
		for (int i = 1; i < n && nr_intervals > 0; i++) {
			for (int j = 1; j <= nr_intervals; j++) {
				caught[i][j] = caught[i - 1][j], from[i][j] = j;
				for (int k = j - 1, f = fi[i], c = f; k >= 0; k--) {
					if (caught[i][j] < caught[i - 1][k] + c)
						caught[i][j] = caught[i - 1][k] + c, from[i][j] = k;
					if ((f -= di[i]) > 0)
						c += f;
				}
			}
			if (caught[max_i][max_j] < caught[i][nr_intervals])
				max_i = i, max_j = nr_intervals;
			nr_intervals -= ti[i];
		}
#ifdef DEBUG
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= h * 60 / interval; j++)
				if (caught[i][j])
					printf("[%d][%d]: (%d %d) ", i, j, caught[i][j], from[i][j]);
			putchar('\n');
		}
		printf("%d %d\n", max_i, max_j);
#endif
		print_intervals(max_i, max_j);
		for (int i = max_i; i < n - 1; i++)
			printf(", 0");
		printf("\nNumber of fish expected: %d\n", caught[max_i][max_j]);
	}
	return 0;
}

