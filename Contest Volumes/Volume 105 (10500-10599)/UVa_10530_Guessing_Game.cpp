
/*
	UVa 10530 - Guessing Game

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10530_Guessing_Game.cpp
*/

#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
	while (true) {
		int n;
		const int nr_chars_max = 16;
		char s[nr_chars_max], t[nr_chars_max];
		const int nr_numbers = 10;
		bool too_lows[nr_numbers + 1], too_highs[nr_numbers + 1];
			// too_lows[i], too_highs[i] is true if the number of i has been guessed
		memset(too_lows, 0, sizeof(too_lows));
		memset(too_highs, 0, sizeof(too_highs));
		while (true) {
			scanf("%d", &n);
			if (!n)
				break;
			scanf("%s %s", s, t);
			if (!strcmp(s, "right"))
				break;
			else if (!strcmp(t, "high"))
				too_highs[n] = true;
			else
				too_lows[n] = true;
		}
		if (!n)
			break;
		else {
			bool dishonest = false;
			for (int i = n; i; i--)
				if (too_highs[i])
					dishonest = true;
			if (!dishonest) {
				for (int i = n; i <= nr_numbers; i++)
					if (too_lows[i])
						dishonest = true;
			}
			if (dishonest)
				printf("Stan is dishonest\n");
			else
				printf("Stan may be honest\n");
		}
	}
	return 0;
}

