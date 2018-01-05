
/*
	UVa 10976 - Fractions Again?!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10976_Fractions_Again.cpp
*/

#include <cstdio>

/*
	xy = k * (x + y) --> x = (y * k) / (y - k), k < y <= x <= 2 * k
*/

const int k_max = 10000;
struct fraction {
	int x_, y_;
} fractions[k_max];

int main()
{
	int k;
	while (scanf("%d", &k) != EOF) {
		int n = 0;
		for (int y = k + 1; y <= 2 * k; y++) {
			int x = k * y;
			if (!(x % (y - k))) {
				fractions[n].x_ = x / (y - k);
				fractions[n].y_ = y;
				n++;
			}
		}
		printf("%d\n", n);
		for (int i = 0; i < n; i++)
			printf("1/%d = 1/%d + 1/%d\n", k, fractions[i].x_, fractions[i].y_);
	}
	return 0;
}

