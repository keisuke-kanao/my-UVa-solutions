
/*
	UVa 10008 - What's Cryptanalysis?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10008_Whats_Cryptanalysis.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

const int nr_letters = 26;

struct occurrence {
	char letter_;
	int count_;

	bool operator<(const occurrence& o) const {
		if (count_ > o.count_)
			return true;
		else if (count_ < o.count_)
			return false;
		else
			return letter_ < o.letter_;
	}
} occurrences[nr_letters];

int main()
{
	for (int i = 0; i < nr_letters; i++) {
		occurrences[i].letter_ = static_cast<char>('A' + i);
		occurrences[i].count_ = 0;
	}
	int n;
	cin >> n;
	string s;
	getline(cin, s);
	while (n--) {
		getline(cin, s);
		for (const char* p = s.c_str(); *p; p++) {
			char c = *p;
			if (isalpha(c))
				occurrences[toupper(c) - 'A'].count_++;
		}
	}
	sort(occurrences, occurrences + nr_letters);
	for (int i = 0; i < nr_letters; i++) {
		if (!occurrences[i].count_)
			break;
		cout << occurrences[i].letter_ << ' ' << occurrences[i].count_ << endl;
	}
	return 0;
}

