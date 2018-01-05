
/*
	UVa 10625 - GNU = GNU'sNotUnix

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10625_GNUsNotUnix.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const char ascii_char_min = 33, ascii_char_max = 126;
const int nr_ascii_chars = ascii_char_max - ascii_char_min + 1, nr_chars_max = 127;

struct freq {
	char c_;
	int ctr_;

	bool operator<(const freq& f) const {return ctr_ > f.ctr_;}
};

struct rule {
	freq freqs_[nr_ascii_chars];
};

rule rules[nr_ascii_chars];

#ifdef DEBUG
void print_ctrs(const unsigned long long* ctrs)
{
	for (int i = 0; i < nr_ascii_chars; i++)
		if (ctrs[i])
			printf("%c: %d ", ascii_char_min + i, ctrs[i]);
	putchar('\n');
}
#endif

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		for (int i = 0; i < nr_ascii_chars; i++)
			for (int j = 0; j < nr_ascii_chars; j++) {
				rules[i].freqs_[j].c_ = ascii_char_min + j;
				rules[i].freqs_[j].ctr_ = 0;
			}
		int R;
		scanf("%d", &R);
		while (R--) {
			char s[nr_chars_max + 1];
			scanf("%s", s);
			if (strlen(s) > 3) {
				const char* p = s;
				rule& r = rules[*p - ascii_char_min];
				for (p += 3; *p; p++)
					r.freqs_[*p - ascii_char_min].ctr_++;
				sort(r.freqs_, r.freqs_ + nr_ascii_chars);
			}
		}
		int Q;
		scanf("%d", &Q);
		while (Q--) {
			char s[nr_chars_max + 1], x[2];
			int n;
			scanf("%s %s %d", s, x, &n);
			unsigned long long ctrs[nr_ascii_chars], tctrs[nr_ascii_chars];
			memset(ctrs, 0, sizeof(ctrs));
			memset(tctrs, 0, sizeof(tctrs));
			for (const char* p = s; *p; p++)
				ctrs[*p - ascii_char_min]++;
#ifdef DEBUG
			print_ctrs(ctrs);
#endif
			while (n--) {
				for (int i = 0; i < nr_ascii_chars; i++)
					if (ctrs[i]) {
						const rule& r = rules[i];
						for (int j = 0; j < nr_ascii_chars && r.freqs_[j].ctr_; j++)
							tctrs[r.freqs_[j].c_ - ascii_char_min] += ctrs[i] * r.freqs_[j].ctr_;
						if (!r.freqs_[0].ctr_)
							tctrs[i] += ctrs[i];
					}
				memcpy(ctrs, tctrs, sizeof(ctrs));
				memset(tctrs, 0, sizeof(tctrs));
#ifdef DEBUG
				print_ctrs(ctrs);
#endif
			}
			printf("%llu\n", ctrs[x[0] - ascii_char_min]);
		}
	}
	return 0;
}

/*
Sample Input

2
3
G->GNU's
N->Not
U->Unix
2
GNU t 3
GNU N 3
1
A->BAcX
1
ABCcXA c 10000

Sample Output

6
4
20001


2
3
G->GNGU's
N->Not
U->Unix
2
GNU t 3
GNU N 3
1
A->BAcAX
1
ABCcXA c 10000

7
8
18446744073709551615

1
3
G->GNGU's
N->not
U->Unix
2
GNU t 3
GNU N 3

4
4
*/

