
/*
	UVa 11048 - Automatic Correction of Misspellings

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11048_Automatic_Correction_of_Misspellings.cpp

	Another accepted solution, run time = 0.066, ranking = 48.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int nr_words_max = 10000, nr_chars_max = 25;
char words[nr_words_max + 1][nr_chars_max + 1], sorted_words[nr_words_max + 1][nr_chars_max + 1];

int compare_word(const void* i, const void* j)
{
	return strcmp(reinterpret_cast<const char*>(i), reinterpret_cast<const char*>(j));
}

int correct_or_misspelling(const char* w, const char* s)
{
	while (*w && *s && *w == *s)
		w++, s++;
	if (!*w && !*s)
		return 1; // correct
	else if (!strcmp(w + 1, s) || !strcmp(w, s + 1) || !strcmp(w + 1, s + 1))
		return 0;
	else if (*(w + 1) == *s && *w == *(s + 1) && !strcmp(w + 2, s + 2))
		return 0;
	else
		return -1;
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", words[i]);
		strcpy(sorted_words[i], words[i]);
	}
	qsort(sorted_words, n, nr_chars_max + 1, compare_word);
	int q;
	scanf("%d", &q);
	while (q--) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		if (bsearch(s, sorted_words, n, nr_chars_max + 1, compare_word))
			printf("%s is correct\n", s);
		else {
			int misspelling = -1;
			for (int i = 0; i < n; i++)
				if (correct_or_misspelling(words[i], s) == 0) {
					misspelling = i;
					break;
				}
			if (misspelling != -1)
				printf("%s is a misspelling of %s\n", s, words[misspelling]);
			else
				printf("%s is unknown\n", s);
		}
	}
	return 0;
}

