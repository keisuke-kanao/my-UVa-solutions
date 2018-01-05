
/*
	UVa 10333 - The Tower of ASCII

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10333_The_Tower_of_ASCII.cpp
*/

#include <cstdio>

const int H_max = 500;
int nr_lefts, nr_rights, lefts[H_max], rights[H_max], left_heights[H_max + 1], right_heights[H_max + 1];

int main()
{
	int H;
	for (int t = 1; scanf("%d", &H) != EOF; t++) {
		nr_lefts = 0, nr_rights = 0;
		for (int lh = 1, h = H; ; lh++) {
			if (h - lh > lh) {
				lefts[nr_lefts++] = lh;
				h -= lh;
			}
			else {
				lefts[nr_lefts++] = h;
				break;
			}
		}
		for (int i = 0; i < nr_lefts - 1; i++)
			rights[nr_rights++] = lefts[i];
		rights[nr_rights - 1] += lefts[nr_lefts - 1];
		left_heights[0] = right_heights[0] = 0;
		for (int i = 1; i <= nr_lefts; i++)
			left_heights[i] = left_heights[i - 1] + lefts[i - 1];
		for (int i = 1; i <= nr_rights; i++)
			right_heights[i] = right_heights[i - 1] + rights[i - 1];
#ifdef DEBUG
		printf("left heights: ");
		for (int i = 0; i <= nr_lefts; i++)
			printf(" %d%c", left_heights[i], ((i < nr_lefts) ? ' ' : '\n'));
		printf("right heights: ");
		for (int i = 0; i <= nr_rights; i++)
			printf(" %d%c", right_heights[i], ((i < nr_rights) ? ' ' : '\n'));
#endif
		printf("Tower #%d\n", t);

		int indent = nr_lefts - 1;
		for (int i = 0; i < indent; i++)
			printf("  ");
		puts("#****#");
		for (int h = 1, lh = 1, rh = 1, w = 4; h < H; h++) {
			if (h == left_heights[lh])
				indent--;
			for (int i = 0; i < indent; i++)
				printf("  ");
			if (h == left_heights[lh])
				printf("#**");
			else
				putchar('#');
			for (int i = 0; i < w; i++)
				putchar('.');
			if (h == right_heights[rh])
				puts("**#");
			else
				puts("#");
			if (h == left_heights[lh])
				w += 2;
			else if (h + 1 == left_heights[lh + 1])
				lh++;
			if (h == right_heights[rh])
				w += 2;
			else if (h + 1 == right_heights[rh + 1])
				rh++;
		}
		putchar('\n');
	}
	return 0;
}

