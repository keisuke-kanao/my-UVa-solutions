
/*
	UVa 10646 - What is the Card?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10646_What_is_the_Card.cpp
*/

#include <cstdio>
#include <cctype>

int main()
{
	const int nr_cchars = 2, nr_pcards_max = 27, nr_hcards = 25;
	char pile[nr_pcards_max][nr_cchars + 1], hand[nr_hcards][nr_cchars + 1];
	int t;
	scanf("%d\n", &t);
	for (int sn = 1; sn <= t; sn++) {
		for (int i = 0; i < nr_pcards_max; i++)
			scanf("%s", pile[i]);
		for (int i = 0; i < nr_hcards; i++)
			scanf("%s", hand[i]);
		int x, y = 0, nr_pcards = nr_pcards_max;
		for (int i = 0; i < 3; i++) {
			x = (isdigit(pile[nr_pcards - 1][0])) ? pile[nr_pcards - 1][0] - '0' : 10;
			y += x;
			nr_pcards -= 11 - x;
		}
		char* p = (y > nr_pcards) ? hand[y - 1 - nr_pcards] : pile[y - 1];
		printf("Case %d: %s\n", sn, p);
	}
	return 0;
}

