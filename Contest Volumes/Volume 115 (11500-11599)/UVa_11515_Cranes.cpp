
/*
	UVa 11515 - Cranes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11515_Cranes.cpp
*/

/*
Applied dynamic programming.
areas[i] is the areas with the bitmap i of cranes' usage where each bit of i corresponds to the i-th crane.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int C_max = 15;

struct crane {
	int x_, y_, r_;
} cranes[C_max];

bool overlapped[C_max][C_max];
	// overlapped[i][j] is true if the covering areas of i-th crane and j-th crane are overlapped
int areas[1 << C_max];
	// areas[i] is the areas with the bitmap i of cranes' usage

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int C;
		scanf("%d", &C);
		for (int i = 0; i < C; i++)
			scanf("%d %d %d", &cranes[i].x_, &cranes[i].y_, &cranes[i].r_);
		memset(overlapped, 0, sizeof(overlapped));
		for (int i = 0; i < C - 1; i++)
			for (int j = i + 1; j < C; j++) {
				int dx = cranes[i].x_ - cranes[j].x_, dy = cranes[i].y_ - cranes[j].y_,
					dr = cranes[i].r_ + cranes[j].r_;
				if (dx * dx + dy * dy <= dr * dr)
					overlapped[i][j] = overlapped[j][i] = true;
			}
		memset(areas, 0, sizeof(int) * (1 << C));
		areas[1] = cranes[0].r_ * cranes[0].r_;
#ifdef DEBUG
		printf("[1]:%d\n", areas[1]);
#endif
		for (int i = 1, ib = 1 << 1; i < C; i++, ib <<= 1) {
			int a = cranes[i].r_ * cranes[i].r_;
			for (int j = 1; j < ib; j++)
				if (areas[j]) {
					int k, kb;
					for (k = 0, kb = 1; k < i; k++, kb <<= 1)
						if (j & kb && overlapped[i][k])
							break;
					if (k == i) // not overlapped
						areas[j | ib] = areas[j] + a;
				}
			areas[ib] = a;
#ifdef DEBUG
			for (int j = 1; j < 1 << ib; j++)
				if (areas[j])
					printf("[%d]:%d ", j, areas[j]);
			putchar('\n');
#endif
		}
		int max_area = 0;
		for (int j = 1; j < 1 << C; j++)
			max_area = max(max_area, areas[j]);
		printf("%d\n", max_area);
	}
	return 0;
}

