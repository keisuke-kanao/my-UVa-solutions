
/*
	UVa 11683 - Laser Sculpture

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11683_Laser_Sculpture.cpp
*/

#include <cstdio>

const int C_max = 10000;
int heights[C_max];

int main()
{
	while (true) {
		int A, C;
		scanf("%d %d", &A, &C);
		if (!A && !C)
			break;
		for (int i = 0; i < C; i++)
			scanf("%d", &heights[i]);
		int nr = 0;
		for (int i = 0, depth = 0; i < C; i++) {
			int d = A - heights[i];
			if (d > depth)
				nr += d - depth;
			depth = d;
		}
/*
		int d = A - heights[0], depth = d, max_depth = d;
		int nr = d;
		for (int i = 1; i < C; i++) {
			int d = A - heights[i];
			if (d > depth)
				nr++;
			if (d > max_depth) {
				nr += d - max_depth;
				max_depth = d;
			}
			depth = d;
		}
*/
		printf("%d\n", nr);
	}
	return 0;
}

