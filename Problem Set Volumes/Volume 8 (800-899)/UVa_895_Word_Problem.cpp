
/*
	UVa 895 - Word Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_895_Word_Problem.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_letters = 26;
const int nr_words_max = 1000, nr_chars_word_max = 10;
char word_letter_frequencies[nr_words_max][nr_letters];
char letter_frequencies[nr_letters];

int main()
{
	int nr_words = 0;
	while (true) {
		char w[nr_chars_word_max + 1];
		gets(w);
		if (w[0] == '#')
			break;
		for (const char* p = w; *p; p++)
			word_letter_frequencies[nr_words][*p - 'a']++;
		nr_words++;
	}
	while (true) {
		memset(letter_frequencies, 0, sizeof(letter_frequencies));
		char c;
		while ((c = getchar()) != '\n' && c != '#') {
			if (!isspace(c))
				letter_frequencies[c - 'a']++;
		}
		if (c == '#')
			break;
		int nr_occurrences = 0;
		for (int i = 0; i < nr_words; i++) {
			int j;
			for (j = 0; j < nr_letters; j++)
				if (word_letter_frequencies[i][j] > letter_frequencies[j])
					break;
			if (j == nr_letters)
				nr_occurrences++;
		}
		printf("%d\n", nr_occurrences);
	}
	return 0;
}

