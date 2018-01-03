
/*
	UVa 671 - Spell checker

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_671_Spell_checker.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_words_max = 10000, nr_chars_max = 15;
char words[nr_words_max + 1][nr_chars_max + 1];
int replaceables[nr_words_max];

int correct_or_replaceable(const char* w, const char* s)
{
	while (*w && *s && *w == *s)
		w++, s++;
	if (!*w && !*s)
		return 1; // correct
	else if (!strcmp(w + 1, s) || !strcmp(w, s + 1) || !strcmp(w + 1, s + 1))
		return 0;
	else
		return -1;
}

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		int nr_words = 0;
		while (true) {
			scanf("%s", words[nr_words]);
			if (words[nr_words][0] == '#')
				break;
			nr_words++;
		}
		while (true) {
			char s[nr_chars_max + 1];
			scanf("%s", s);
			if (s[0] == '#')
				break;
			int correct = -1, nr_replaceables = 0;
			for (int i = 0; i < nr_words; i++) {
				int cr = correct_or_replaceable(words[i], s);
				if (cr == 1) { // correct
					correct = i;
					break;
				}
				else if (cr == 0) // replaceable
					replaceables[nr_replaceables++] = i;
			}
			if (correct != -1)
				printf("%s is correct\n", s);
			else {
				printf("%s:", s);
				for (int i = 0; i < nr_replaceables; i++)
					printf(" %s", words[replaceables[i]]);
				putchar('\n');
			}
		}
		if (N)
			putchar('\n');
	}
	return 0;
}

