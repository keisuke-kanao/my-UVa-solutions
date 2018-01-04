
/*
	UVa 148 - Anagram checker

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_148_Anagram_checker.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_words_max = 2000, nr_letters = 26;

struct word {
	bool found_; // true if this word was found in the phrases
	string s_;
	int length_;
	int freqs_[nr_letters];

	bool operator<(const word& w) const {return s_ < w.s_;}
};

vector<word> words(nr_words_max + 1);

string phrases;
int afreqs[nr_letters], pfreqs[nr_letters];
int anagram_words[nr_words_max]; // indices of words that consist of an anagram

void anagram(int n, int wi, int awn, int pfn, int afn)
{
	int i;
	if (pfn == afn) {
		for (i = 0; i < awn; i++)
			if (!words[anagram_words[i]].found_)
				break;
		if (i < awn) { // some words are not original ones
			cout << phrases << " = ";
			for (int i = 0; i < awn; i++) {
				if (i)
					cout << ' ';
				cout << words[anagram_words[i]].s_;
			}
			cout << endl;
		}
	}
	else if (wi < n) {
		const word& w = words[wi];
		if (w.length_ + afn <= pfn) {
			for (i = 0; i < nr_letters; i++) {
				if (afreqs[i] + w.freqs_[i] > pfreqs[i])
					break;
				afreqs[i] += w.freqs_[i];
			}
			if (i == nr_letters) {
				anagram_words[awn] = wi;
				anagram(n, wi + 1, awn + 1, pfn, afn + w.length_);
			}
			for (i--; i >= 0; i--)
				afreqs[i] -= w.freqs_[i];
		}
		anagram(n, wi + 1, awn, pfn, afn);
	}
}

int main()
{
	int n = 0;
	while (true) {
		word& w = words[n];
		getline(cin, w.s_);
		if (w.s_ == "#")
			break;
		w.length_ = w.s_.length();
		memset(w.freqs_, 0, sizeof(w.freqs_));
		for (const char* p = w.s_.c_str(); *p; p++)
			w.freqs_[*p - 'A']++;
		n++;
	}
	words.resize(n);
	while (true) {
		getline(cin, phrases);
		if (phrases == "#")
			break;
		for (int i = 0; i < n; i++)
			words[i].found_ = false;
		int pfn = 0;
		memset(pfreqs, 0, sizeof(pfreqs));
		for (const char *p = phrases.c_str(), *q = NULL; ; p++) {
			if (isupper(*p)) {
				pfreqs[*p - 'A']++;
				if (!q)
					q = p;
				pfn++;
			}
			else {
				word w;
				w.s_ = string(q, p - q);
				pair<vector<word>::iterator, vector<word>::iterator> bounds =
					equal_range(words.begin(), words.end(), w);
				for (vector<word>::iterator i = bounds.first, e = bounds.second; i != e; ++i)
					i->found_ = true;
				q = NULL;
			}
			if (!*p)
				break;
		}
		memset(afreqs, 0, sizeof(afreqs));
		anagram(n, 0, 0, pfn, 0);
	}
	return 0;
}

