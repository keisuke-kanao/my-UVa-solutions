
/*
	UVa 11860 - Document Analyzer

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11860_Document_Analyzer.cpp
*/

#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_words_max = 100000;
int positions[nr_words_max]; // positions[i] is the word number of i-th word
int word_ctrs[nr_words_max]; // word_ctrs[i] is the number of word whose number is i

int main()
{
	int T;
	scanf("%d", &T);
	while (getchar() != '\n')
		;
	for (int t = 1; t <= T; t++) {
		int nr_words = 0, nr_positions = 0;
		map<string, int> words;
		while (true) {
			const int nr_chars_max = 150;
			char s[nr_chars_max + 1];
			gets(s);
			if (strstr(s, "END"))
				break;
			for (const char *ps = s, *qs = s; *ps; ) {
 				while (*ps && !islower(*ps))
					ps++;
				if (*ps) {
					qs = ps++;
					while (*ps && islower(*ps))
						ps++;
					pair<map<string, int>::iterator, bool> result = words.insert(make_pair(string(qs, ps - qs), nr_words));
					positions[nr_positions++] = result.first->second;
					if (result.second)
						word_ctrs[nr_words++] = 0;
				}
			}
		}
		int min_p = 0, min_q = nr_positions, nr = 0;
		for (int p = 0, q = 0; p < nr_positions && q <= nr_positions; ) {
			if (nr == nr_words) {
				if (q - p < min_q - min_p)
					min_p = p, min_q = q;
				if (!--word_ctrs[positions[p]])
					nr--;
				p++;
			}
			else {
				if (q < nr_positions && !word_ctrs[positions[q]]++)
					nr++;
				q++;
			}
		}
		printf("Document %d: %d %d\n", t, min_p + 1, min_q);
	}
	return 0;
}

