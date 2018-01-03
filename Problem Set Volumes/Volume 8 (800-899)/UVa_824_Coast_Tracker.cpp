
/*
	UVa 824 - Coast Tracker

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_824_Coast_Tracker.cpp
*/

/*
Starting from the east side (index 6) to north east (index 7) ... 0, 1, 2, 3, 4, until south east side (index 5), 
  check whether that position is a land, if yes, output that direction.

Alternative: Ad-hoc. Just follow the instruction and rotate the direction appropriately looking for the first land.

*/

#include <cstdio>

int main()
{
	const int nr_dirs = 8;
	const int dirs[nr_dirs][2] = {
		{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}
	};
	const int dir_indices[nr_dirs] = {6, 7, 0, 1, 2, 3, 4, 5};

	while (true) {
		int x, y, d, i, j, xi, yi, si;
		scanf("%d", &x);
		if (x == -1)
			break;
		scanf("%d %d", &y, &d);
		int surroundings[nr_dirs];
		for (i = 0; i < nr_dirs; i++) {
			scanf("%d %d %d", &xi, &yi, &si);
			xi -= x, yi -= y;
			for (j = 0; j < nr_dirs; j++)
				if (xi == dirs[j][0] && yi == dirs[j][1]) {
					surroundings[j] = si;
					break;
				}
		}
#ifdef DEBUG
		for (i = 0; i < nr_dirs; i++)
			printf("%d%c", surroundings[i], ((i < nr_dirs - 1) ? ' ' : '\n'));
#endif
		for (i = 0; i < nr_dirs; i++, d = (d + 1) % nr_dirs)
			if (surroundings[d])
				break;
		printf("%d\n", dir_indices[d]);
	}
	return 0;
}

