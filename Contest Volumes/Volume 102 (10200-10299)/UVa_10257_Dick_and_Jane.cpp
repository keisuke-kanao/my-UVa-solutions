
/*
	UVa 10257 - Dick and Jane

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10257_Dick_and_Jane.cpp
*/

#include <cstdio>

int main()
{
	const int d = 12;
	int s, p, y, j;
	while (scanf("%d %d %d %d", &s, &p, &y, &j) != EOF) {
		j += d;
		int ya = (j - (p + y)) / 3;
		int sa, pa;
		switch ((j - (p + y)) % 3) {
		case 0:
			sa = ya + y; pa = ya + p;
			break;
		case 1:
			if (s + p == y) {
				sa = ya + y + 1; pa = ya + p;
			}
			else {
				sa = ya + y; pa = ya + p + 1;
			}
			break;
		case 2:
			sa = ya + y + 1; pa = ya + p + 1;
			break;
		}
		printf("%d %d %d\n", sa, pa, ya);
	}
	return 0;
}

