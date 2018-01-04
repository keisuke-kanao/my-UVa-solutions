
/*
	UVa 12611 - Beautiful Flag

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12611_Beautiful_Flag.cpp
*/

#include <cstdio>

int main()
{
	int t;
	scanf("%d", &t);
	for (int c = 1; c <= t; c++) {
		int radius;
		scanf("%d", &radius);
		int length = radius * 5, width = radius * 3;
		printf("Case %d:\n", c);
		int left = -(length * 9) / 20, right = (length * 11) / 20, upper = width / 2, lower = -width / 2;
		printf("%d %d\n", left, upper);
		printf("%d %d\n", right, upper);
		printf("%d %d\n", right, lower);
		printf("%d %d\n", left, lower);
	}
	return 0;
}

