
/*
	UVa 10100 - Longest Match

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10100_Longest_Match.cpp
*/

#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_chars_max = 1000, nr_word_chars_max = 20;

struct word {
   char s_[nr_word_chars_max + 1];

	word() {s_[0] = '\0';}
	word(const char* s, int length) {strncpy(s_, s, length); s_[length] = '\0';}
	bool operator<(const word& w) const {return strcmp(s_, w.s_) < 0;}
	bool operator==(const word& w) const {return !strcmp(s_, w.s_);}
};

map<word, int> words;
char s[nr_chars_max + 1], t[nr_chars_max + 1];
int swords[nr_chars_max], twords[nr_chars_max];
int lcs[2][nr_chars_max + 1];

int register_words(char* s, int length, int ws[])
{
	int nw = 1;
	for (int i = 0; i < length; i++)
		if (!isspace(s[i]) && !ispunct(s[i])) {
			int j = i + 1;
			for ( ; j < length; j++)
				if (isspace(s[j]) || ispunct(s[j]))
					break;
			pair<map<word, int>::iterator, bool> result =
				words.insert(make_pair(word(s + i, j - i), static_cast<int>(words.size())));
			ws[nw++] = result.first->second;
			i = j;
		}
	return nw - 1;
}

int longest_common_subsequence(int slen, int tlen)
{
	for (int i = 0; i <= tlen; i++)
		lcs[0][i] = 0;
	lcs[1][0] = 0;
	for (int i = 1; i <= slen; i++) {
		int *clcs = lcs[i % 2], *plcs = lcs[(i - 1) % 2];
		for (int j = 1; j <= tlen; j++) {
			if (swords[i] == twords[j])
				clcs[j] = plcs[j - 1] + 1;
			else
				clcs[j] = max(clcs[j - 1], plcs[j]);
		}
	}
	return lcs[slen % 2][tlen];
}

/*
function LCSLength(X[1..m], Y[1..n])
    C = array(0..m, 0..n)
    for i := 0..m
       C[i,0] = 0
    for j := 0..n
       C[0,j] = 0
    for i := 1..m
        for j := 1..n
            if X[i] = Y[j]
                C[i,j] := C[i-1,j-1] + 1
            else
                C[i,j] := max(C[i,j-1], C[i-1,j])
    return C[m,n]
*/

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		if (!gets(s))
			break;
		gets(t);
		printf("%2d. ", case_nr);
		int slen = strlen(s), tlen = strlen(t);
		if (!slen || !tlen)
			printf("Blank!\n");
		else {
			words.clear();
			int swlen = register_words(s, slen, swords);
			int twlen = register_words(t, tlen, twords);
			int lcs = longest_common_subsequence(swlen, twlen);
			printf("Length of longest match: %d\n", lcs);
		}
	}
	return 0;
}

