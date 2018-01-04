
/*
	UVa 179 - Code Breaking

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_179_Code_Breaking.cpp

	This is an accepted solution.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
using namespace std;

const int nr_chars_max = 80;
char plaintext[nr_chars_max + 1], cyphertext1[nr_chars_max + 1], cyphertext2[nr_chars_max + 1];
bool overall_mappings[nr_chars_max][nr_chars_max], mappings[nr_chars_max][nr_chars_max];
bool mapped[nr_chars_max];
int permutation[nr_chars_max], inverse_permutation[nr_chars_max];

bool permutable(int k, int length)
{
	const int nr_letters = 128;
	int pfreqs[nr_letters], cfreqs[nr_letters];
	for (int i = 0; i + k < length; i += k) {
		memset(pfreqs, 0, sizeof(pfreqs));
		memset(cfreqs, 0, sizeof(cfreqs));
		for (int j = 0; j < k && i + j < length; j++) {
			pfreqs[plaintext[i + j]]++;
			cfreqs[cyphertext1[i + j]]++;
		}
		for (int j = 0; j < nr_letters; j++)
			if (pfreqs[j] != cfreqs[j])
				return false;
	}
    return true;
}

void get_mappings(int i, int k, int length)
{
	for (int j = 0; j < length; j++)
		mappings[i][j] = true;
	for (int p = i; p < length; p += k) {
		bool tmp[nr_chars_max];
		for (int j = 0; j < length; j++)
			tmp[j] = false;
		int b = (p / k) * k;
		for (int j = b; j < b + k; j++) {
#ifndef ONLINE_JUDGE
			assert(j - b < length);
#endif
			if (j >= length || overall_mappings[p][j])
				tmp[j - b] = true;
		}
		for (int j = 0; j < length; j++)
			mappings[i][j] &= tmp[j];
	}
/*
	for (int j = 0; j < length; j++)
		mappings[i][j] = true;
	for (int p = i; p < length; p += k) {
		int b = (p / k) * k; // round down to the nearest boundary
		for (int j = b; j < b + k; j++) {
#ifndef ONLINE_JUDGE
			assert(j - b < length);
#endif
			if (j >= length || overall_mappings[p][j])
				mappings[i][j - b] = false;
		}
	}
*/
}

struct candidate {
    int i_;
    int ctr_;
bool operator<(const candidate& c) const {return ctr_ < c.ctr_;}
} candidates[nr_chars_max];

bool backtrack(int ci, int k)
{
	if (ci == k)
		return true;
	for (int i = 0; i < k; i++)
		if (mappings[candidates[ci].i_][i] && !mapped[i]) {
			permutation[candidates[ci].i_] = i;
			mapped[i] = true;
			if (backtrack(ci + 1, k))
				return true;
			mapped[i] = false;
		}
	return false;
}

bool get_permutation(int k, int length)
{
	for (int i = 0; i < k; i++) {
		candidates[i].i_ = i;
		int ctr = 0;
		for (int j = 0; j < length; j++)
			if (mappings[i][j])
				ctr++;
		candidates[i].ctr_ = ctr;
	}
	sort(candidates, candidates + k);
	for (int i = 0; i < k; i++)
		mapped[i] = false;
	return backtrack(0, k);
}

void print_permutation(int k)
{
	printf("%d:", k);
	for (int i = 0; i < k; i++)
		printf(" %d->%d", i, permutation[i]);
	putchar('\n');
}

void decrypt(int k, int length)
{
	int l = strlen(cyphertext2);
	length = (l + k - 1) / k * k;
	memset(cyphertext2 + l, '?', length - l);
	for (int i = 0; i < k; i++)
		inverse_permutation[i] = permutation[i];
	const char* pc = cyphertext2;
	char* pp = plaintext;
	for (int i = 0; i < length; i += k, pc += k)
		for (int j = 0; j < k; j++)
			*pp++ = pc[inverse_permutation[j]];
	*pp = '\0';
	puts(plaintext);
}

int main()
{
	while (true) {
		gets(plaintext);
		if (!strcmp(plaintext, "#"))
			break;
		gets(cyphertext1);
		gets(cyphertext2);
		int length = strlen(plaintext);
		for (int i = 0; i < length; i++)
			for (int j = 0; j < length; j++)
				overall_mappings[i][j] = plaintext[i] == cyphertext1[j];
		bool found = false;
		for (int k = 1; k <= length && !found; k++) {
			if (permutable(k, length)) {
				bool abort = false;
				for (int i = 0; !abort && i < k; i++) {
					get_mappings(i, k, length);
					int j;
					for (j = 0; j < length; j++)
						if (mappings[i][j])
							break;
					if (j == length)
						abort = true;
				}
				if (!abort) {
					if (found = get_permutation(k, length)) {
#ifdef DEBUG
						print_permutation(k);
#endif
						decrypt(k, length);
					}
				}
			}
		}
		if (!found)
			puts(cyphertext2);
	}
	return 0;
}

