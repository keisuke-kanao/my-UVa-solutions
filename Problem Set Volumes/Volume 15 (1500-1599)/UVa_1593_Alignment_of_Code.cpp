
/*
	UVa 1593 - Alignment of Code

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1593_Alignment_of_Code.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 180, nr_lines_max = 1000;

char lines[nr_lines_max][nr_chars_max + 1], buff[nr_chars_max * nr_chars_max];

struct word {
	char* p_;
	int l_;
} words[nr_lines_max][nr_chars_max + 1];

int max_lengths[nr_chars_max + 1];

int main()
{
	int nr_lines = 0;
	while (gets(lines[nr_lines])) {
		char* p = lines[nr_lines];
		while (*p == ' ')
			p++;
		for (int i = 0; *p; i++) {
			words[nr_lines][i].p_ = p;
			while (*p && *p != ' ')
				p++;
			words[nr_lines][i].l_ = p - words[nr_lines][i].p_;
			max_lengths[i] = max(max_lengths[i], words[nr_lines][i].l_ + 1);
			while (*p == ' ')
				p++;
		}
		nr_lines++;
	}
	for (int i = 0; i < nr_lines; i++) {
		char* p = buff;
		for (int j = 0; words[i][j].p_; j++) {
			memcpy(p, words[i][j].p_, words[i][j].l_);
			p += words[i][j].l_;
			if (words[i][j + 1].p_) {
				int k = max_lengths[j] - words[i][j].l_;
				memset(p, ' ', k);
				p += k;
			}
		}
		*p = '\0';
		puts(buff);
	}
	return 0;
}

