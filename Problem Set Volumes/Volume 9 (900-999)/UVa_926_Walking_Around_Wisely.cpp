
/*
	UVa 926 - Walking Around Wisely

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_926_Walking_Around_Wisely.cpp
*/

#include <cstdio>
#include <cstring>

const int n_max = 30;

long long nr_ways[n_max + 1][n_max + 1];
bool not_allowed_from_south[n_max + 1][n_max + 1], not_allowed_from_west[n_max + 1][n_max + 1];

int main()
{
	int C;
	scanf("%d", &C);
	while (C--) {
		memset(nr_ways, 0, sizeof(nr_ways));
		memset(not_allowed_from_south, 0, sizeof(not_allowed_from_south));
		memset(not_allowed_from_west, 0, sizeof(not_allowed_from_west));
		int N;
		scanf("%d", &N);
		int sx, sy, ex, ey;
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		int W;
		scanf("%d", &W);
		while (W--) {
			int Px, Py;
			char D[2];
			scanf("%d %d %s", &Px, &Py, D);
			if (D[0] == 'N' || D[0] == 'S') {
				if (D[0] == 'S')
					Py--;
				not_allowed_from_south[Px][Py] = true;
			}
			else {
				if (D[0] == 'W')
					Px--;
				not_allowed_from_west[Px][Py] = true;
			}
		}
		nr_ways[sx][sy] = 1;
		for (int y = sy + 1; y <= ey; y++)
			if (!not_allowed_from_south[sx][y - 1])
				nr_ways[sx][y] += nr_ways[sx][y - 1];
		for (int x = sx + 1; x <= ex; x++)
			for (int y = sy; y <= ey; y++) {
				if (!not_allowed_from_south[x][y - 1])
					nr_ways[x][y] += nr_ways[x][y - 1];
				if (!not_allowed_from_west[x - 1][y])
					nr_ways[x][y] += nr_ways[x - 1][y];
			}
		printf("%lld\n", nr_ways[ex][ey]);
	}
	return 0;
}

