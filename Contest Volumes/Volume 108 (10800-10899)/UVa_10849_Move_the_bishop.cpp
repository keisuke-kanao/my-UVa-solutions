
/*
	UVa 10849 - Move the bishop

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10849_Move_the_bishop.cpp
*/

#include <cstdio>
#include <cstdlib>

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		int t, n;
		scanf("%d %d", &t, &n);
		while (t--) {
			int r1, r2, c1, c2;
			scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
			int m = -1;
			if (r1 < 1 || r1 > n || c1 < 1 || c1 > n ||
				r2 < 1 || r2 > n || c2 < 1 || c2 > n ||
				(r1 + c1) % 2 != (r2 + c2) % 2)
				;
			else if (r1 == r2 && c1 == c2)
				m = 0;
			else if (abs(r1 - r2) == abs(c1 - c2))
				m = 1;
			else
				m = 2;
			if (m < 0)
				printf("no move\n");
			else
				printf("%d\n", m);
		}
	}
	return 0;
}

