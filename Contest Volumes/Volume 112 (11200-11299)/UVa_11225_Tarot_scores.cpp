
/*
	UVa 11225 - Tarot scores

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11225_Tarot_scores.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int nr_chars_max = 31;
	int T;
	scanf("%d", &T);
	for (int h = 1; h <= T; h++) {
		int M;
		scanf("%d", &M);
		char s[nr_chars_max + 1], t[nr_chars_max + 1];
		int nr_points = 0, nr_oudlers = 0;
		while (M--) {
			scanf("%s", s);
			if (!strcmp(s, "fool")) {
				nr_points += 45;
				nr_oudlers++;
			}
			else {
				scanf("%*s%s", t);
				if (!strcmp(s, "king"))
					nr_points += 45;
 				else if (!strcmp(t, "trumps") && (!strcmp(s, "one") || !strcmp(s, "twenty-one"))) {
					nr_points += 45;
					nr_oudlers++;
				}
				else if (!strcmp(s, "queen"))
					nr_points += 35;
				else if (!strcmp(s, "knight"))
					nr_points += 25;
				else if (!strcmp(s, "jack"))
					nr_points += 15;
				else
					nr_points += 5;
			}
		}
		switch (nr_oudlers) {
		case 3:
			nr_points -= 360; break;
		case 2:
			nr_points -= 410; break;
		case 1:
			nr_points -= 510; break;
		default:
			nr_points -= 560; break;
		}
		printf("Hand #%d\n", h);
		if (nr_points < 0)
			printf("Game lost by %d point(s).\n", -nr_points / 10);
		else
			printf("Game won by %d point(s).\n", nr_points / 10);
		if (h < T)
			putchar('\n');
	}
	return 0;
}

