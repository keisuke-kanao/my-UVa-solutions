
/*
	UVa 12463 - Little Nephew

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12463_Little_Nephew.cpp
*/

#include <cstdio>

int main()
{
	while (true) {
		int a, b, c, d, e;
		scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
		if (!a)
			break;
		printf("%d\n", a * b * c * d * d * e * e);
	}
	return 0;
}

