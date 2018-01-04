
/*
	UVa 168 - Theseus and the Minotaur

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_168_Theseus_and_the_Minotaur.cpp

	from ACM South Pacific Regionals 1991 Problem E
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1991/index.html)
*/

#include <cstdio>

const int nr_letters = 26;

struct cavern {
	int reachables_[nr_letters + 1];
	bool candle_;
} caverns[nr_letters];

int main()
{
	const int nr_chars_max = 255;
	char s[nr_chars_max + 1];
	while (true) {
		scanf("%s", s);
		if (s[0] == '#')
			break;
		cavern caverns[nr_letters];
		for (int i = 0; i < nr_letters; i++) {
			caverns[i].reachables_[0] = -1;
			caverns[i].candle_ = false;
		}
		for (const char* p = s; *p; p++) {
			int i = *p++ - 'A', j = 0;
			for (p++; *p >= 'A' && *p <= 'Z'; p++)
				caverns[i].reachables_[j++] = *p - 'A';
			caverns[i].reachables_[j] = -1; // terminator
		}
		char mc[1 + 1], tc[1 + 1];
		int mi, pmi, k, ki = 1;
		scanf("%s %s %d", mc, tc, &k);
		mi = mc[0] - 'A', pmi = tc[0] - 'A';
		int np = 0, passed[nr_letters];
		while (true) {
#ifdef DEBUG
			printf("%d %d\n", pmi, mi);
#endif
			if (pmi == mi) {
				if (!caverns[mi].candle_)
					passed[np++] = mi;
				break;
			}
			if (ki == k) {
				ki = 0;
#ifdef DEBUG
				printf("%d\n", mi);
#endif
				caverns[mi].candle_ = true;
				passed[np++] = mi;
			}
			const int* pc;
			for (pc = caverns[mi].reachables_; *pc != -1; pc++)
				if (*pc != pmi && !caverns[*pc].candle_)
					break;
			if (*pc == -1) {
				if (!caverns[mi].candle_)
					passed[np++] = mi;
				break;
			}
			else {
				pmi = mi;
				mi = *pc;
				ki++;
			}
		}
		for (int i = 0; i < np; i++) {
			if (i)
				putchar(' ');
			if (i == np - 1)
				putchar('/');
			putchar(passed[i] + 'A');
		}
		putchar('\n');
	}
	return 0;
}


