
/*
	UVa 554 - Caesar Cypher

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_554_Caesar_Cypher.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int nr_words_max = 100, nr_word_chars_max = 20,
	nr_encrypted_chars_max = 250, nr_decrypted_chars_max = 60, K_max = 27;

char words[nr_words_max + 1][nr_word_chars_max + 1];
const char* pwords[nr_words_max + 1];

int compare_words(const void* s, const void* t)
{
	const char** p = (const char**)s;
	const char** q = (const char**)t;
	return strcmp(*p, *q);
}

int main()
{
	int nr_words = 0;
	while (true) {
		gets(words[nr_words]);
		if (words[nr_words][0] == '#')
			break;
		pwords[nr_words] = &words[nr_words][0];
		nr_words++;
	}
	qsort(pwords, nr_words, sizeof(char*), compare_words);
	char s[nr_encrypted_chars_max + 1];
	gets(s);
	char t[nr_encrypted_chars_max + 1];
	int max_nr_matches = 0, max_k;
	char *p, *q, *r;
	for (int k = 0; k < K_max; k++) {
		for (p = s, q = t; *p; p++, q++) {
			int i = (*p == ' ') ? k : (*p - 'A' + 1 + k) % K_max;
			*q = (i) ? 'A' + i - 1 : ' ';
		}
		*q = '\0';
		int nr_matches = 0;
		for (p = t, q = t; ; ) {
			while (*q && *q != ' ')
				q++;
			if (*q) {
				*q = '\0';
				if (bsearch(&p, pwords, nr_words, sizeof(char*), compare_words))
					nr_matches++;
				p = ++q;
			}
			else {
				if (bsearch(&p, pwords, nr_words, sizeof(char*), compare_words))
					nr_matches++;
				break;
			}
		}
		if (nr_matches > max_nr_matches)
			max_nr_matches = nr_matches, max_k = k;
	}
#ifdef DEBUG
	printf("%d %d\n", max_nr_matches, max_k);
#endif
	for (p = s, q = t; *p; p++, q++) {
		int i = (*p == ' ') ? max_k : (*p - 'A' + 1 + max_k) % K_max;
		*q = (i) ? 'A' + i - 1 : ' ';
	}
#ifdef DEBUG
	printf("%s\n", t);
#endif
	for (p = t, q = t, r = t; ; ) {
		while (*q && *q != ' ')
			q++;
		if (q - r > nr_decrypted_chars_max) {
			char* pp = p;
			while (pp > r && *(pp - 1) == ' ')
				pp--;
			*pp = '\0';
			puts(r);
			r = p;
		}
		if (*q)
			p = ++q;
		else {
			char* pp = p;
			while (pp > r && *(pp - 1) == ' ')
				pp--;
			*pp = '\0';
			puts(r);
			break;
		}
	}
	return 0;
}

