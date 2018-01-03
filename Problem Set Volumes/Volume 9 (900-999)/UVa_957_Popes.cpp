
/*
	UVa 957 - Popes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_957_Popes.cpp
*/

#include <cstdio>

const int p_max = 100000;
int years[p_max];

int main()
{
	int y;
	while (scanf("%d", &y) != EOF) {
		int p, i, j, max_popes = 0, max_p, max_i, max_j;
		scanf("%d", &p);
		for (i = 0; i < p; i++)
			scanf("%d", &years[i]);
		if (p == 1) {
			max_popes = 1; max_i = max_j = 0;
		}
		else {
			i = j = 0;
			do {
				if (years[j] - years[i] < y)
					j++;
				else {
					if ((max_p = j - i) > max_popes) {
						max_popes = max_p;
						max_i = i; max_j = j - 1;
					}
					i++;
					if (j < i)
						j = i;
				}
			} while (j < p);
			if ((max_p = j - i) > max_popes) {
				max_popes = max_p;
				max_i = i; max_j = j - 1;
			}
		}
		printf("%d %d %d\n", max_popes, years[max_i], years[max_j]);
	}
	return 0;
}

