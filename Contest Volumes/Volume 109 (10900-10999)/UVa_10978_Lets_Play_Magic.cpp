
/*
	UVa 10978 - Let's Play Magic!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10978_Lets_Play_Magic.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	while (true) {
		const int n_max = 52, nr_chars_card = 2;
		char cards[n_max][nr_chars_card + 1];
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cards[i][0] = '\0';
		int ci = -1;
		for (int i = 0; i < n; i++) {
			const int nr_chars_max = 20;
			char card[nr_chars_card + 1], number[nr_chars_max + 1];
			scanf("%s %s", card, number);
			int j = strlen(number);
			do {
				if (++ci == n)
					ci = 0;
				if (!cards[ci][0])
					j--;
			} while (j);
			strcpy(cards[ci], card);
		}
		for (int i = 0; i < n; i++)
			printf("%s%c", cards[i], ((i < n - 1) ? ' ' : '\n'));
	}
	return 0;
}

