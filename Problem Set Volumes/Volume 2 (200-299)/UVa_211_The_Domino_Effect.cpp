
/*
	UVa 211 - The Domino Effect

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_211_The_Domino_Effect.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_bones = 28, nr_rows = 7, nr_cols = 8;

const int bones[nr_bones][2] = {
	{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6},
	{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6},
	{2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6},
	{3, 3}, {3, 4}, {3, 5}, {3, 6},
	{4, 4}, {4, 5}, {4, 6},
	{5, 5}, {5, 6},
	{6, 6}
};

int grid[nr_rows][nr_cols], nr_maps, map[nr_rows][nr_cols];

void print_grid_or_map(int grid_or_map[nr_rows][nr_cols])
{
	for (int i = 0; i < nr_rows; i++) {
		for (int j = 0; j < nr_cols; j++)
			printf("%4d", grid_or_map[i][j]);
		putchar('\n');
	}
	putchar('\n');
}

void domino_effect(int bi)
{
	if (bi == nr_bones) {
		nr_maps++;
		print_grid_or_map(map);
		return;
	}
	int pf = bones[bi][0], ps = bones[bi][1], bn = bi + 1;
	for (int i = 0; i < nr_rows; i++)
		for (int j = 0; j < nr_cols; j++) {
			if (j < nr_cols - 1 && !map[i][j] && !map[i][j + 1] &&
				(grid[i][j] == pf && grid[i][j + 1] == ps || grid[i][j] == ps && grid[i][j + 1] == pf)) {
				map[i][j] = map[i][j + 1] = bn;
				domino_effect(bi + 1);
				map[i][j] = map[i][j + 1] = 0;
			}
			if (i < nr_rows - 1 && !map[i][j] && !map[i + 1][j] &&
				(grid[i][j] == pf && grid[i + 1][j] == ps || grid[i][j] == ps && grid[i + 1][j] == pf)) {
				map[i][j] = map[i + 1][j] = bn;
				domino_effect(bi + 1);
				map[i][j] = map[i + 1][j] = 0;
			}
		}
}

int main()
{
	for (int ln = 1; ; ln++) {
		if (scanf("%d", &grid[0][0]) == EOF)
			break;
		for (int j = 1; j < nr_cols; j++)
			scanf("%d", &grid[0][j]);
		for (int i = 1; i < nr_rows; i++)
			for (int j = 0; j < nr_cols; j++)
				scanf("%d", &grid[i][j]);
		if (ln > 1)
			printf("\n\n\n");
		printf("Layout #%d:\n\n", ln);
		print_grid_or_map(grid);
		printf("Maps resulting from layout #%d are:\n\n", ln);
		nr_maps = 0;
		memset(map, 0, sizeof(map));
		domino_effect(0);
		printf("There are %d solution(s) for layout #%d.\n", nr_maps, ln);
	}
	return 0;
}

