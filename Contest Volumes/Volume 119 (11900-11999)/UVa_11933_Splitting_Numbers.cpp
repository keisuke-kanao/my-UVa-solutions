
/*
	UVa 11933 - Splitting Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11933_Splitting_Numbers.cpp
*/

#include <cstdio>

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int an = 0, bn = 0;
		for (int b = 1, i = 1; n; b <<= 1, n >>= 1)
			if (n & 1) {
				if (i & 1)
					an |= b;
				else
					bn |= b;
				i++;
			}
		printf("%d %d\n", an, bn);
	}
	return 0;
}

