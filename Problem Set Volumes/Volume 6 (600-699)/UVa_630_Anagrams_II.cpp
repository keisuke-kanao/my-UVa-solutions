
/*
	UVa 630 - Anagrams (II)

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_630_Anagrams_II.cpp
*/

#include <cstdio>
#include <cstring>

const int n_max = 1000;
const int nr_letters = 'z' - 'a' + 1, nr_chars_max = 20;

struct word {
	char s_[nr_chars_max + 1];
	char freqs_[nr_letters]; // freqs_[i] is the number of occurrences of ('a' + i)

	void count_freqs();
} words[n_max];

void word::count_freqs()
{
	memset(freqs_, 0, sizeof(freqs_));
	for (const char* p = s_; *p; p++)
		freqs_[*p - 'a']++;
}

int main()
{
	int m;
	scanf("%d", &m);
	while (m--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", words[i].s_);
			words[i].count_freqs();
		}
		while (true) {
			word w;
			scanf("%s", w.s_);
			if (w.s_[0] == 'E')
				break;
			w.count_freqs();
			printf("Anagrams for: %s\n", w.s_);
			int j = 0;
			for (int i = 0; i < n; i++)
				if (!memcmp(words[i].freqs_, w.freqs_, nr_letters))
					printf("%3d) %s\n", ++j, words[i].s_);
			if (!j)
				printf("No anagrams for: %s\n", w.s_);
		}
		if (m)
			putchar('\n');
	}
	return 0;
}

