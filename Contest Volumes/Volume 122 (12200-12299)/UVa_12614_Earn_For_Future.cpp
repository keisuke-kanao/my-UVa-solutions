
/*
	UVa 12614 - Earn For Future

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12614_Earn_For_Future.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		scanf("%d", &N);
		int max_C = -1;
		while (N--) {
			int C;
			scanf("%d", &C);
			if (C > max_C)
				max_C = C;
		}
		printf("Case %d: %d\n", t, max_C);
	}
	return 0;
}

