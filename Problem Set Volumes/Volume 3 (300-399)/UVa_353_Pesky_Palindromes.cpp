
/*
	UVa 353 - Pesky Palindromes

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_353_Pesky_Palindromes.cpp
*/

#include <set>
#include <cstdio>
#include <cstring>
using namespace std;

struct substring {
	const char* s_;
	int length_;
	substring(const char* s, int length) : s_(s), length_(length) {}
	bool operator<(const substring& ss) const;
	bool is_palindrome() const;
};

bool substring::operator<(const substring& ss) const
{
	for (int i = 0; i < length_ && i < ss.length_; i++) {
		if (s_[i] < ss.s_[i])
			return true;
		else if (s_[i] > ss.s_[i])
			return false;
	}
	return length_ < ss.length_;
}

bool substring::is_palindrome() const
{
	for (int i = 0, j = length_ - 1; i < j; i++, j--)
		if (s_[i] != s_[j])
			return false;
	return true;
}

int main()
{
	const int nr_chars_max = 80;
	char s[nr_chars_max + 1];
	while (gets(s)) {
		set<substring> substrings;
		for (int l = 1, length = strlen(s); l <= length; l++)
			for (int i = 0; i + l <= length; i++) {
				substring ss(s + i, l);
				set<substring>::const_iterator j = substrings.find(ss);
				if (j == substrings.end() && ss.is_palindrome())
					substrings.insert(ss);
			}
		printf("The string '%s' contains %d palindromes.\n", s, substrings.size());
	}
	return 0;
}

