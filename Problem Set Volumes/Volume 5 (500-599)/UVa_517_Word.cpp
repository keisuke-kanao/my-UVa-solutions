
/*
	UVa 517 - Word

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_517_Word.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_chars_max = 15, nr_rules = 8, nr_words_max = 1 << nr_chars_max;

int visited[nr_words_max];
int nr_words, words[nr_words_max];

int word_to_value(int word, int wi, int length)
{
	int value = 0;
	for (int i = 0, b = 1 << (length - 1);
		i < length; i++, b >>= 1, wi = (wi - 1 + length) % length)
		if (word & (1 << wi))
			value += b;
	return value;
}

int get_min_word(int word, int length)
{
	int min_word = 1 << length;
	for (int i = 0; i < length; i++)
		min_word = min(min_word, word_to_value(word, i, length));
	return min_word;
}

void print_word(int word, int length)
{
	for (int i = 0, b = 1 << (length - 1); i < length; i++, b >>= 1)
		putchar((word & b) ? 'b' : 'a');
	putchar('\n');
}

struct rule {
	int c1_, c2_, c3_, c4_;
};

int main()
{
	int length, steps;
	char s[nr_chars_max + 1];
	rule rules[nr_rules];
	while (scanf("%d", &length) != EOF) {
		for (int i = 0, j = 1 << length; i < j; i++)
			visited[i] = -1;
		nr_words = 0;
		scanf("%s", s);
		int word = 0, next_word;
		for (int i = 0, b = 1 << (length - 1); i < length; i++, b >>= 1)
			if (s[i] == 'b')
				word += b;
		word = get_min_word(word, length);
		for (int i = 0; i < nr_rules; i++) {
			scanf("%s", s);
			rules[i].c1_ = (s[0] == 'b') ? 1 : 0;
			rules[i].c2_ = (s[1] == 'b') ? 1 : 0;
			rules[i].c3_ = (s[2] == 'b') ? 1 : 0;
			rules[i].c4_ = (s[3] == 'b') ? 1 : 0;
		}
		scanf("%d", &steps);
		int cycle_start = -1, cycle_length = 0;
		for (int i = 0; i < steps; i++) {
			int next_word = word;
			for (int j = 0; j < nr_rules; j++) {
				const rule& r = rules[j];
				for (int k = 0; k < length; k++) {
					int k1 = (k + 2) % length, k3 = (k - 1 + length) % length;
					if ((word & (1 << k1)) >> k1 == r.c1_ &&
						(word & (1 << k)) >> k == r.c2_ &&
						(word & (1 << k3)) >> k3 == r.c3_) {
						if (r.c4_)
							next_word |= 1 << k;
						else
							next_word &= ~(1 << k);
					}
				}
			}
			word = get_min_word(next_word, length);
			if (visited[word] != -1) {
				cycle_start = visited[word];
				cycle_length = nr_words - cycle_start;
				break;
			}
			else {
				visited[word] = nr_words;
				words[nr_words++] = word;
			}
		}
#ifdef DEBUG
		printf("%d\n", nr_words);
		for (int i = 0; i < nr_words; i++)
			print_word(words[i], length);
#endif
		if (nr_words < steps) {
#ifdef DEBUG
			printf("%d %d\n", cycle_start, cycle_length);
#endif
			word = words[cycle_start + (steps - cycle_start - 1) % cycle_length];
		}
		print_word(word, length);
	}
	return 0;
}

