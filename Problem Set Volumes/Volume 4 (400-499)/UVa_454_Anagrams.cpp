
/*
	UVa 454 - Anagrams

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_454_Anagrams.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_letters = 128;

struct phrase {
	string s_;
	int freqs_[nr_letters];

	phrase() {}
	phrase(const string& s) : s_(s) {memset(freqs_, 0, sizeof(freqs_));}

	bool operator<(const phrase& p) const {return s_ < p.s_;}
};

int main()
{
	string line;
	getline(cin, line);
	istringstream iss(line);
	int t;
	iss >> t;
	getline(cin, line);
	while (t--) {
		vector<phrase> phrases;
		while (getline(cin, line) && !line.empty()) {
			phrases.push_back(phrase(line));
			phrase& p = phrases.back();
			for (const char* q = p.s_.c_str(); *q; q++)
				if (!isspace(*q))
					p.freqs_[*q]++;
		}
		int n = static_cast<int>(phrases.size());
		sort(phrases.begin(), phrases.end());
		for (int i = 0; i < n - 1; i++) {
			const phrase& pi = phrases[i];
			for (int j = i + 1; j < n; j++) {
				const phrase& pj = phrases[j];
				int k;
				for (k = 0; k < nr_letters; k++)
					if (pi.freqs_[k] != pj.freqs_[k])
						break;
				if (k == nr_letters)
					cout << pi.s_ << " = " << pj.s_ << endl;
			}
		}
		if (t)
			cout << endl;
	}
	return 0;
}

