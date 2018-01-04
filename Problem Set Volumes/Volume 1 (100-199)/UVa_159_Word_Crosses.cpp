
/*
	UVa 159 - Word Crosses

	To build using Visucal Studio 2010:
		cl -EHsc -O2 UVa_159_Word_Crosses.cpp
*/

#include <utility>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 31;

struct word_cross {
	char hw[nr_chars_max + 1], vw[nr_chars_max + 1]; // horizontal/vertical word
	int hl, vl; // horizontal/vertical length
	int hi, vi; // horizontal/vertical common letter indices
};

bool find_letter_indices(word_cross& wcs)
{
	const int nr_letters = 26;
	pair<int, int> indices[nr_letters];
		// indices[i].first/second is the minimum horizontal/vertical index of letter ('A' + i)
	for (int i = 0; i < nr_letters; i++) {
		indices[i].first = wcs.hl;
		indices[i].second = wcs.vl;
	}
	for (int i = 0; i < wcs.hl; i++) {
		int hi = wcs.hw[i] - 'A';
		indices[hi].first = min(indices[hi].first, i);
	}
	for (int i = 0; i < wcs.vl; i++) {
		int vi = wcs.vw[i] - 'A';
		indices[vi].second = min(indices[vi].second, i);
	}
	sort(indices, indices + nr_letters);
	for (int i = 0; i < nr_letters; i++)
		if (indices[i].first < wcs.hl && indices[i].second < wcs.vl) {
			wcs.hi = indices[i].first; wcs.vi = indices[i].second;
			return true;
		}
	return false;
}

void print_spaces(int ns)
{
	while (ns--)
		putchar(' ');
}

int main()
{
	word_cross wcs[2];
	bool printed = false;
	while (true) {
		scanf("%s", wcs[0].hw);
		if (wcs[0].hw[0] == '#')
			break;
		if (printed)
			putchar('\n');
		else
			printed = true;
		scanf("%s %s %s", wcs[0].vw, wcs[1].hw, wcs[1].vw);
		wcs[0].hl = strlen(wcs[0].hw); wcs[0].vl = strlen(wcs[0].vw);
		wcs[1].hl = strlen(wcs[1].hw); wcs[1].vl = strlen(wcs[1].vw);
		if (find_letter_indices(wcs[0]) && find_letter_indices(wcs[1])) {
			int vi = max(wcs[0].vi, wcs[1].vi);
			int vl = vi + max(wcs[0].vl - wcs[0].vi, wcs[1].vl - wcs[1].vi);
			// fill the begining part of vertical word with spaces
			if (vi > wcs[0].vi) {
				int c = vi - wcs[0].vi;
				memmove(&(wcs[0].vw[c]), wcs[0].vw, wcs[0].vl);
				memset(wcs[0].vw, ' ', c);
				wcs[0].vl += c;
			}
			else if (vi > wcs[1].vi) {
				int c = vi - wcs[1].vi;
				memmove(&(wcs[1].vw[c]), wcs[1].vw, wcs[1].vl);
				memset(wcs[1].vw, ' ', c);
				wcs[1].vl += c;
			}
			int nhs = wcs[0].hl - wcs[0].hi + 2 + wcs[1].hi;
				// number of horizontal spaces between vertical words
			for (int i = 0; i < vl; i++) {
				if (i == vi)
					printf("%s   %s\n", wcs[0].hw, wcs[1].hw);
				else {
					print_spaces(wcs[0].hi);
					if (i < wcs[0].vl) {
						putchar(wcs[0].vw[i]);
						if (i < wcs[1].vl && wcs[1].vw[i] != ' ') {
							print_spaces(nhs);
							putchar(wcs[1].vw[i]);
						}
					}
					else {
						print_spaces(nhs + 1);
						putchar(wcs[1].vw[i]);
					}
					putchar('\n');
				}
			}
		}
		else
			puts("Unable to make two crosses");
	}
	return 0;
}

