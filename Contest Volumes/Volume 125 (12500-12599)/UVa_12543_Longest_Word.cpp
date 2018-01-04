
/*
	UVa 12543 - Longest Word

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_12543_Longest_Word.cpp
*/

#include <cstdio>
#include <cstring>
#include <cctype>

const int nr_chars_max = 10000;
char word[nr_chars_max + 1], longest_word[nr_chars_max + 1];

int main()
{
	int max_length = 0;
	while (true) {
		scanf("%s", word);
		if (!strcmp(word, "E-N-D"))
			break;
		const char* p = word;
		do {
			for ( ; *p; p++)
				if (isalpha(*p) || *p == '-')
					break;
			if (*p) {
				int length = 1;
				const char* q = p;
				for (q++; *q; q++, length++)
					if (!isalpha(*q) && *q != '-')
						break;
				if (length > max_length) {
					max_length = length;
					char* r = longest_word;
					for ( ; p < q; r++, p++)
						*r = tolower(*p);
					*r = '\0';
				}
				p = q;
			}
		} while (*p);
	}
	printf("%s\n", longest_word);
	return 0;
}

