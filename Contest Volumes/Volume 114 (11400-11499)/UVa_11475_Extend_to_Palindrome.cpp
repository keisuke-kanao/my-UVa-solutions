
/*
	UVa 11475 - Extend to Palindrome

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11475_Extend_to_Palindrome.cpp
*/

#include <iostream>
#include <string>
using namespace std;

class Kmp {
public:
	Kmp(const string& pattern);
	~Kmp() {delete[] failure_;}
	int match(const string& text);

private:
	int* failure_;
	const string pattern_;
};

Kmp::Kmp(const string& pattern)
	: failure_(new int[pattern.size() + 1]), pattern_(pattern)
{
    // build failure function
	failure_[0] = failure_[1] = 0;
	for (int i = 2; i <= pattern_.size(); i++) {
		for (int j = failure_[i - 1]; ; j = failure_[j]) {
			if (pattern_[j] == pattern_[i - 1]) {
				failure_[i] = j + 1; break;
			}
			if (!j) {
				failure_[i] = 0; break;
			}
		}
	}
}

int Kmp::match(const string& text) {
	for (int i = 0, j = 0; ;) {
		if (j == text.size())
			return i;
		if (text[j] == pattern_[i]) {
			i++; j++;
		}
		else if (i > 0)
			i = failure_[i];
		else
			j++;
	}
}

int main()
{
	string s;
	while (cin >> s) {
		// find the maximum of n such that s.substr(s.size() - n) == s_rev.substr(0, N)
		string s_rev(s.rbegin(), s.rend());
		Kmp kmp(s_rev);
		int max_match = kmp.match(s);
		cout << s + s_rev.substr(max_match) << endl;
	}
	return 0;
}

