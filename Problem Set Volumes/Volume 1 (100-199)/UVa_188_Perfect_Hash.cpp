
/*
	UVa 188 - Perfect Hash

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_188_Perfect_Hash.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

unsigned int convert_word_to_number(const string& word)
{
	unsigned int n = 0;
	for (const char* p = word.c_str(); *p; p++) {
		n <<= 5;
		n |= *p - 'a' + 1;
	}
	return n;
}

unsigned int resolve_conflicts(unsigned int c, int n, const vector<unsigned int>& words)
{
	unsigned int c_candidate = 0;
	for (int i = 0; i < n; i++) {
		unsigned int hi = (c / words[i]) % n;
		unsigned int hi_candidate = (c / words[i] + 1) * words[i];
		for (int j = i + 1; j < n; j++) {
			unsigned int hj = (c / words[j]) % n;
			if (hi == hj) // a conflict
				c_candidate = max(c_candidate, min(hi_candidate, (c / words[j] + 1) * words[j]));
		}
	}
	return c_candidate; // if no conflicts, return 0, else, return the largest candicate of C
}

int main()
{
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		string word;
		set<unsigned int> s;
		while (iss >> word)
			s.insert(convert_word_to_number(word));
		vector<unsigned int> words(s.begin(), s.end());
		int n = words.size();
		unsigned int c = words[0];
		while (true) {
#ifdef DEBUG
			cout << c << endl;
#endif
			unsigned int c_candidate = resolve_conflicts(c, n, words);
			if (!c_candidate)
				break;
			c = c_candidate;
		}
		cout << line << endl << c << endl << endl;
	}
	return 0;
}

