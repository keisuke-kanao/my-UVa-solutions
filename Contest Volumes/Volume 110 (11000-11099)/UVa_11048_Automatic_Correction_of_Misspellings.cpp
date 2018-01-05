
/*
	UVa 11048 - Automatic Correction of Misspellings

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11048_Automatic_Correction_of_Misspellings.cpp

	An accepted solution, run time = 0.109, ranking = 104.
*/

#include <cstdio>
#include <cstring>

const int nr_words_max = 10000, nr_chars_max = 25;
char words[nr_words_max + 1][nr_chars_max + 1];

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
	for (int i = 0; i < n; i++)
		scanf("%s", words[i]);
	int q;
	scanf("%d", &q);
	while (q--) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int correct = -1, misspelling = -1;
		for (int i = 0; i < n; i++) {
			int cm = correct_or_misspelling(words[i], s);
			if (cm == 1) { // correct
				correct = i;
				break;
			}
			else if (cm == 0 && misspelling == -1)
				misspelling = i;
		}
		if (correct != -1)
			printf("%s is correct\n", s);
		else if (misspelling != -1)
			printf("%s is a misspelling of %s\n", s, words[misspelling]);
		else
			printf("%s is unknown\n", s);
	}
	return 0;
}

/*
Sample Input

10
this
is
a
dictionary
that
we
will
use
for
us
6
su
as
the
dictonary
us
willl

Sample Output

su is a misspelling of us
as is a misspelling of is
the is unknown
dictonary is a misspelling of dictionary
us is correct
willl is a misspelling of will

*/

