
/*
	UVa 10662 - The Wedding

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10662_The_Wedding.cpp
*/

#include <cstdio>

const int trh_max = 20;
int tr[trh_max][trh_max], rh[trh_max][trh_max], ht[trh_max][trh_max];

void read_input(int r, int c, int trh[trh_max][trh_max])
{
	for (int i = 0; i < r; i++) {
		int p;
		scanf("%d", &p);
		for (int j = 0; j < c; j++) {
			int k;
			scanf("%d", &k);
			trh[i][j] = (k) ? 0 : p;
		}
	}
}

int main()
{
	int t, r, h;
	while (scanf("%d %d %d", &t, &r, &h) != EOF) {
		read_input(t, r, tr);
		read_input(r, h, rh);
		read_input(h, t, ht);
		int cheapest = -1, ct, cr, ch;
		for (int i = 0; i < t; i++)
			for (int j = 0; j < r; j++)
				if (tr[i][j]) {
					for (int k = 0; k < h; k++)
						if (rh[j][k] && ht[k][i]) {
							int p = tr[i][j] + rh[j][k] + ht[k][i];
							if (cheapest == -1 || p < cheapest) {
								cheapest = p;
								ct = i; cr = j; ch = k;
							}
						}
				}
		if (cheapest == -1)
			puts("Don't get married!");
		else
			printf("%d %d %d:%d\n", ct, cr, ch, cheapest);
	}
	return 0;
}

