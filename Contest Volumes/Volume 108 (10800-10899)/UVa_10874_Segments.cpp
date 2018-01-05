
/*
	UVa 10874 - Segments

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10874_Segments.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 20000;

enum {left, right};
int segments[n_max][right - left + 1];
	// segments[i][left/right] is the left/right side of the i-th segments
int paths[n_max][right - left + 1];
	// paths[i][left/right] is the shortest path from (1, 1) to the left/right side of the i-th segments

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			scanf("%d %d", &segments[i][left], &segments[i][right]);
		paths[0][left] = n + segments[0][right] - segments[0][left] - 1, paths[0][right] = segments[0][right] - 1;
#ifdef DEBUG
		printf("[0][%d]: %d\t[0][%d]: %d\n", left, paths[0][left], right, paths[0][right]);
#endif
		for (int i = 1; i < n; i++) {
			int sd = segments[i][right] - segments[i][left];
			int ld, rd;
			if (segments[i - 1][left] < segments[i][right])
				ld = segments[i][right] - segments[i - 1][left];
			else
				ld = segments[i - 1][left] - segments[i][right];
			if (segments[i - 1][right] < segments[i][right])
				rd = segments[i][right] - segments[i - 1][right];
			else
				rd = segments[i - 1][right] - segments[i][right];
			paths[i][left] = min(paths[i - 1][left] + ld + sd, paths[i - 1][right] + rd + sd) + 1;
			if (segments[i - 1][left] < segments[i][left])
				ld = segments[i][left] - segments[i - 1][left];
			else
				ld = segments[i - 1][left] - segments[i][left];
			if (segments[i - 1][right] < segments[i][left])
				rd = segments[i][left] - segments[i - 1][right];
			else
				rd = segments[i - 1][right] - segments[i][left];
			paths[i][right] = min(paths[i - 1][left] + ld + sd, paths[i - 1][right] + rd + sd) + 1;
#ifdef DEBUG
			printf("[%d][%d]: %d\t[%d][%d]: %d\n",
				i, left, paths[i][left], i, right, paths[i][right]);
#endif
		}
		printf("%d\n",
			min(paths[n - 1][left] + n - segments[n - 1][left], paths[n - 1][right] + n - segments[n - 1][right]));
	}
	return 0;
}

