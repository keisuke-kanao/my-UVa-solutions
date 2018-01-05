
/*
	UVa 10950 - Bad Code

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10950_Bad_Code.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_letters = 26, nr_code_chars_max = 3, nr_encrypted_chars_max = 100;

struct code {
	char c_;
	int l_;
	char s_[nr_code_chars_max + 1];

	bool operator<(const code& c) const {return c_ < c.c_;}
} codes[nr_letters];

char encrypted[nr_encrypted_chars_max + 1], text[nr_encrypted_chars_max + 1];

bool plain_text(int n, int el, int ei, int ti, int& nr)
{
	if (ei == el) {
		text[ti] = '\0';
		puts(text);
		nr++;
		return nr == 100;
	}
	else {
		for (int ci = 0; ci < n; ci++) {
			const code& c = codes[ci];
			if (el - ei >= c.l_) {
				if (c.l_ == 1 && encrypted[ei] == c.s_[0]) {
					text[ti] = c.c_;
					if (plain_text(n, el, ei + 1, ti + 1, nr))
						return true;
				}
				else if (c.l_ == 2 && encrypted[ei] == c.s_[0] && encrypted[ei + 1] ==  c.s_[1]) {
					text[ti] = c.c_;
					if (plain_text(n, el, ei + 2, ti + 1, nr))
						return true;
				}
			}
			if (encrypted[ei] == '0' && el - ei - 1 >= c.l_) {
				if (c.l_ == 1 && encrypted[ei + 1] == c.s_[0]) {
					text[ti] = c.c_;
					if (plain_text(n, el, ei + 2, ti + 1, nr))
						return true;
				}
				else if (c.l_ == 2 && encrypted[ei + 1] == c.s_[0] && encrypted[ei + 2] ==  c.s_[1]) {
					text[ti] = c.c_;
					if (plain_text(n, el, ei + 3, ti + 1, nr))
						return true;
				}
			}
		}
		return false;
	}
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++) {
			char letter[2];
			scanf("%s", letter);
			code& c = codes[i];
			c.c_ = letter[0];
			scanf("%s", c.s_);
			c.l_ = strlen(c.s_);
		}
		sort(codes, codes + N);
		scanf("%s", encrypted);
		printf("Case #%d\n", case_nr);
		int nr = 0;
		plain_text(N, strlen(encrypted), 0, 0, nr);
		putchar('\n');
	}
	return 0;
}

