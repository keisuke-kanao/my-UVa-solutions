
/*
	UVa 10677 - Base Equality

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10677_Base_Equality.cpp
*/

#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		int B1, B2, r1, r2;
		scanf("%d %d %d %d", &B1, &B2, &r1, &r2);
		int i;
		for (i = r2 - 1; i > r1; i--) {
			int j = i, k = j % B1, l = B2;
			j /= B1;
			while (j) {
				k += (j % B1) * l;
				j /= B1;
				l *= B2;
			}
			if (!(k % i))
				break;
		}
		if (i > r1)
			printf("%d\n", i);
		else
			puts("Non-existent.");
	}
	return 0;
}

