
/*
	UVa 668 - Parliament

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_668_Parliament.cpp
*/

#include <cstdio>
#include <cstring>

/*
4
 5: 2 3
 6: 2 4
 7: 3 4
 8: 3 5

5
 9: 2 3 4                5: + 4
10: 2 3 5                5: + 5
11: 2 4 5                6: + 5
12: 3 4 5                7: + 5
13: 3 4 6                7: + 6

6
14: 2 3 4 5              9: + 5
15: 2 3 4 6              9: + 6
16: 2 3 5 6             10: + 6
17: 2 4 5 6             11: + 6
18: 3 4 5 6             12: + 6
19: 3 4 5 7             12: + 7

7
20: 2 3 4 5 6           14: + 6
21: 2 3 4 5 7           14: + 7
22: 2 3 4 6 7           15: + 7
23: 2 3 5 6 7           16: + 7
24: 2 4 5 6 7           17: + 7
25: 3 4 5 6 7           18: + 7
26: 3 4 5 6 8           18: + 8

8
27: 2 3 4 5 6 7         20: + 7
28: 2 3 4 5 6 8         20: + 8
29: 2 3 4 5 7 8         21: + 8
30: 2 3 4 6 7 8         22: + 8
31: 2 3 5 6 7 8         23: + 8
32: 2 4 5 6 7 8         24: + 8
33: 3 4 5 6 7 8         25: + 8
34: 3 4 5 6 7 9         25: + 9

9
35: 2 3 4 5 6 7 8       27: + 8
36: 2 3 4 5 6 7 9       27: + 9
37: 2 3 4 5 6 8 9       28: + 9
38: 2 3 4 5 7 8 9       29: + 9
39: 2 3 4 6 7 8 9       30: + 9
40: 2 3 5 6 7 8 9       31: + 9
41: 2 4 5 6 7 8 9       32: + 9
42: 3 4 5 6 7 8 9       33: + 9
43: 3 4 5 6 7 8 10      33: + 10
...
*/

const int N_min = 5, N_max = 1000, nr_sizes_max = 45;
int nr_sizes[N_max + 1] = {
	0, 0, 0, 0, 0,
	2, 2, 2, 2
};
int sizes[N_max + 1][nr_sizes_max] = {
	{0}, {0}, {0}, {0}, {0},
	{2, 3}, {2, 4}, {3, 4}, {3, 5}
};

int main()
{
	for (int nr = N_min, pnr = N_min - 1, n = nr + pnr; n <= N_max; pnr = nr++) {
#ifdef DEBUG
		printf("%d\n", nr);
#endif
		for (int i = 0; i < nr && n <= N_max; i++, n++) {
			if (!i) {
				memcpy(sizes[n], sizes[n - pnr], nr_sizes[n - pnr] * sizeof(int));
				sizes[n][nr_sizes[n - pnr]] = pnr;
				nr_sizes[n] = nr_sizes[n - pnr] + 1;
			}
			else if (i == nr - 1) {
				memcpy(sizes[n], sizes[n - pnr - 2], nr_sizes[n - pnr - 2] * sizeof(int));
				sizes[n][nr_sizes[n - pnr - 2]] = nr + 1;
				nr_sizes[n] = nr_sizes[n - pnr - 2] + 1;
			}
			else {
				memcpy(sizes[n], sizes[n - pnr - 1], nr_sizes[n - pnr - 1] * sizeof(int));
				sizes[n][nr_sizes[n - pnr - 1]] = nr;
				nr_sizes[n] = nr_sizes[n - pnr - 1] + 1;
			}
#ifdef DEBUG
			printf("%4d: ", n);
			for (int j = 0; j < nr_sizes[n]; j++)
				printf("%d%c", sizes[n][j], ((j < nr_sizes[n] - 1) ? ' ' : '\n'));
#endif
		}
	}

	int M;
	scanf("%d", &M);
	while (M--) {
		int N;
		scanf("%d", &N);
		for (int j = 0; j < nr_sizes[N]; j++)
			printf("%d%c", sizes[N][j], ((j < nr_sizes[N] - 1) ? ' ' : '\n'));
		if (M)
			putchar('\n');
	}
	return 0;
}

