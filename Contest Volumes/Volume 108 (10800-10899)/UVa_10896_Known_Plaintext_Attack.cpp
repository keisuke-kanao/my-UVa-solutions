
/*
	UVa 10896 - Known Plaintext Attack

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10896_Known_Plaintext_Attack.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_letters = 26;

int get_key(const char* w, const char* e)
{
	int k = *e++ - *w++;
	if (k < 0)
		k += nr_letters;
	for ( ; *w; w++, e++) {
		int i = *e - *w;
		if (i < 0)
			i += nr_letters;
		if (i != k)
			return -1;
	}
	return k;
}

int main()
{
	bool keys[nr_letters]; // keys[i] is true if i + 'a' is a possible key
	const int nr_chars_per_word_max = 16, nr_chars_per_line_max = 70;
	char word[nr_chars_per_word_max + 1], line[nr_chars_per_line_max + 1];
	int n;
	scanf("%d", &n);
	getchar();
	while (n--) {
		gets(line);
		gets(word);
		int length = strlen(word);
		memset(keys, 0, sizeof(keys));
		for (const char *p = line, *q = NULL; ; p++) {
			if (*p == ' ' || !*p) {
				if (p - q == length) {
					int k = get_key(word, q);
					if (k != -1)
						keys[k] = true;
				}
				q = NULL;
			}
			else if (!q)
				q = p;
			if (!*p)
				break;
		}
		for (int i = 0; i < nr_letters; i++)
			if (keys[i])
				putchar('a' + i);
		putchar('\n');
	}
	return 0;
}

