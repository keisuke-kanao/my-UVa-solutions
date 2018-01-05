
/*
	UVa 11345 - Rectangles

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11345_Rectangles.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	int N;
	scanf("%d", &N);
	for (int n = 1; n <= N; n++) {
		int M, max_X1, max_Y1, min_X2, min_Y2;
		scanf("%d", &M);
		scanf("%d %d %d %d", &max_X1, &max_Y1, &min_X2, &min_Y2);
		while (--M) {
			int X1, Y1, X2, Y2;
			scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
			max_X1 = max(max_X1, X1), max_Y1 = max(max_Y1, Y1),
				min_X2 = min(min_X2, X2), min_Y2 = min(min_Y2, Y2);
#ifdef DEBUG
			printf("%d %d %d %d\n", max_X1, max_Y1, min_X2, min_Y2);
#endif
		}
		int area = 0;
		if (max_X1 < min_X2 && max_Y1 < min_Y2)
			area = (min_X2 - max_X1) * (min_Y2 - max_Y1);
		printf("Case %d: %d\n", n, area);
	}
	return 0;
}

