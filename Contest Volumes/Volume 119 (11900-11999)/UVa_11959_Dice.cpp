
/*
	UVa 11959 - Dice

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11959_Dice.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_sides = 6, nr_dice_sides = 24;

int dice_sides[nr_dice_sides][nr_sides] = {
	{0, 1, 2, 3, 4, 5},
	{0, 1, 3, 4, 5, 2},
	{0, 1, 4, 5, 2, 3},
	{0, 1, 5, 2, 3, 4},
	{1, 0, 2, 5, 4, 3},
	{1, 0, 5, 4, 3, 2},
	{1, 0, 4, 3, 2, 5},
	{1, 0, 3, 2, 5, 4},
	{2, 4, 0, 5, 1, 3},
	{2, 4, 5, 1, 3, 0},
	{2, 4, 1, 3, 0, 5},
	{2, 4, 3, 0, 5, 1},
	{4, 2, 0, 3, 1, 5},
	{4, 2, 3, 1, 5, 0},
	{4, 2, 1, 5, 0, 3},
	{4, 2, 5, 0, 3, 1},
	{3, 5, 0, 2, 1, 4},
	{3, 5, 2, 1, 4, 0},
	{3, 5, 1, 4, 0, 2},
	{3, 5, 4, 0, 2, 1},
	{5, 3, 0, 4, 1, 2},
	{5, 3, 4, 1, 2, 0},
	{5, 3, 1, 2, 0, 4},
	{5, 3, 2, 0, 4, 1}
};

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		char s[nr_sides + 1], t[nr_sides + 1];
		scanf("%s %s", s, t);
		bool equal = false;
		for (int i = 0; i < nr_dice_sides; i++) {
			char u[nr_sides];
			for (int j = 0; j < nr_sides; j++)
				u[j] = t[dice_sides[i][j]];
			if (!memcmp(s, u, nr_sides)) {
				equal = true;
				break;
			}
		}
		puts((equal) ? "Equal" : "Not Equal");
	}
	return 0;
}

