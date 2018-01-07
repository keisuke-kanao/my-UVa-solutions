
/*
	UVa 156 - Ananagrams

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_156_Ananagrams.cpp

	from ACM New Zealand Contest 1993 Problem A
		(http://contest.mff.cuni.cz/old/archive/nzl1993a/)
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;

struct word {
	int ananagram_; // 1 for single letter, 0 for a candidate of ananagram, -1 for anagram
	string s_;

	word() : ananagram_(true) {}
	word(const string& s) : ananagram_((s.length() == 1) ? 1 : 0), s_(s) {}
};

int main()
{
	string s;
	set<string> set_of_words;
	while (cin >> s) {
		if (s == "#")
			break;
		set_of_words.insert(s);
	}
	if (!set_of_words.empty()) {
		vector<word> vector_of_words(set_of_words.begin(), set_of_words.end());
		map<string, int> map_of_sorted_words;
			// key is a sorted word, value is the index to vector_of_words
		for (size_t i = 0, e = vector_of_words.size(); i < e; i++) {
			if (vector_of_words[i].ananagram_)
				continue;
			string s(vector_of_words[i].s_);
			transform(s.begin(), s.end(), s.begin(), (int(*)(int))tolower);
			sort(s.begin(), s.end());
			pair<map<string, int>::iterator, bool> result = map_of_sorted_words.insert(make_pair(s, i));
			if (!result.second)
				vector_of_words[i].ananagram_ = vector_of_words[result.first->second].ananagram_ = -1;
		}
		for (size_t i = 0, e = vector_of_words.size(); i < e; i++)
			if (vector_of_words[i].ananagram_ != -1)
				cout << vector_of_words[i].s_ << endl;
	}
	return 0;
}

