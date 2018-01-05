
/*
	UVa 11067 - Little Red Riding Hood

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11067_Little_Red_Riding_Hood.cpp
*/

#include <cstdio>

const int w_max = 128, h_max = 128;

long long nr_paths[w_max][h_max];
bool wolves[w_max][h_max];

int main()
{
	while (true) {
		int w, h;
		scanf("%d %d", &w, &h);
		if (!w && !h)
			break;
		for (int i = 0; i <= h; i++)
			for (int j = 0; j <= w; j++) {
				nr_paths[i][j] = 0;
				wolves[i][j] = false;
			}
		int n;
		scanf("%d", &n);
		while (n--) {
			int x, y;
			scanf("%d %d", &x, &y);
			wolves[y][x] = true;
		}
		nr_paths[0][0] = 1;
		for (int i = 0; i <= h; i++)
			for (int j = 0; j <= w; j++)
				if (!wolves[i][j]) {
					if (i)
						nr_paths[i][j] = nr_paths[i - 1][j];
					if (j)
						nr_paths[i][j] += nr_paths[i][j - 1];
				}
		if (nr_paths[h][w] > 1)
			printf("There are %lld paths from Little Red Riding Hood's house to her grandmother's house.\n", nr_paths[h][w]);
		else if (nr_paths[h][w])
			puts("There is one path from Little Red Riding Hood's house to her grandmother's house.");
		else
			puts("There is no path.");
	}
	return 0;
}

