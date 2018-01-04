
/*
	UVa 12791 - Lap

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12791_Lap.cpp
*/

#include <cstdio>

int main()
{
	int X, Y;
	while (scanf("%d %d", &X, &Y) != EOF) {
		int d = Y - X;
		int lap = Y / d;
		if (Y % d)
			lap++;
		printf("%d\n", lap);
	}
	return 0;
}

