
/*
	UVa 11875 - Brick Game

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11875_Brick_Game.cpp
*/

#include <cstdio>

int main()
{
	int t;
	scanf("%d", &t);
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		const int n_max = 10;
		int n, ages[n_max];
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &ages[i]);
		printf("Case %d: %d\n", case_nr, ages[n / 2]);
	}
	return 0;
}

