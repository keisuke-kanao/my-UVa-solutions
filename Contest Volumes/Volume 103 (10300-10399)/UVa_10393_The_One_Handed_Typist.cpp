
/*
	UVa 10393 - The One-Handed Typist

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10393_The_One_Handed_Typist.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int nr_letters = 128;
const char* keyboard_chars[] = {"", "qaz", "wsx", "edc", "rfvtgb", "", "", "yhnujm", "ik,", "ol.", "p;/"};

const int nr_chars_max = 63, n_max = 1000;

struct word {
	int length_;
	char s_[nr_chars_max + 1];
} words[n_max];

int compare_word(const void* i, const void* j)
{
	const word *wi = reinterpret_cast<const word*>(const_cast<void*>(i)),
		*wj = reinterpret_cast<const word*>(const_cast<void*>(j));
	if (wi->length_ > wj->length_)
		return -1;
	else if (wi->length_ < wj->length_)
		return 1;
	else
		return strcmp(wi->s_, wj->s_);
}

int main()
{
	bool letters[nr_letters]; // letters[i] is true if a letter i can be typed
	int i, j, f, n, m, mm, max_length;
	const char* p;
	while (scanf("%d %d", &f, &n) != EOF) {
		memset(letters, -1, sizeof(letters));
		while (f--) {
			scanf("%d", &i);
			for (p = keyboard_chars[i]; *p; p++)
				letters[*p] = false;
		}
		m = mm = max_length = 0;
		while (n--) {
			scanf("%s", words[m].s_);
			for (p = words[m].s_; *p; p++)
				if (!letters[*p])
					break;
			if (!*p && p - words[m].s_) {
				words[m].length_ = p - words[m].s_;
				if (words[m].length_ > max_length) {
					max_length = words[m].length_;
					mm = 1;
				}
				else if (words[m].length_ == max_length)
					mm++;
				m++;
			}
		}
		qsort(words, m, sizeof(word), compare_word);
#ifdef DEBUG
		for (i = 0; i < m; i++)
			printf("%s%c", words[i].s_, ((i == m - 1) ? '\n' : ' '));
#endif
		for (i = 0, j = mm - 1; i < j; i++) // remove duplicated words
			if (!strcmp(words[i].s_, words[i + 1].s_)) {
				words[i].s_[0] = '\0';
				mm--;
			}
		printf("%d\n", mm);
		for (i = 0, j = 0; j < mm; i++) 
			if (words[i].s_[0]) {
				printf("%s\n", words[i].s_);
				j++;
			}
	}
	return 0;
}

