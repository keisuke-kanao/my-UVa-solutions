
/*
	UVa 11404 - Palindromic Subsequence

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11404_Palindromic_Subsequence.cpp
*/

#include <algorithm>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars_max = 1000;

struct lcs { // longest common subsequence
	int length_;
	string s_;
} lcss[nr_chars_max + 1][nr_chars_max + 1];

int main()
{
	char s[nr_chars_max + 1], rs[nr_chars_max + 1];
	while (scanf("%s", s) != EOF) {
		int length = strlen(s);
		reverse_copy(s, s + length, rs);
		rs[length] = '\0';
		for (int i = 0; i <= length; i++) {
			lcss[0][i].length_ = 0;
			lcss[0][i].s_.clear();
		}
		for (int i = 1; i <= length; i++) {
			for (int j = 1; j <= length; j++) {
				if (s[i - 1] == rs[j - 1]) {
                    lcss[i][j].length_ = lcss[i - 1][j - 1].length_ + 1;
					lcss[i][j].s_ = lcss[i - 1][j - 1].s_ + s[i - 1];
				}
				else {
					if(lcss[i - 1][j].length_ > lcss[i][j - 1].length_) {
                        lcss[i][j].length_ = lcss[i - 1][j].length_;
						lcss[i][j].s_ = lcss[i - 1][j].s_;
                    }
					else if (lcss[i][j - 1].length_ > lcss[i - 1][j].length_) {
                        lcss[i][j].length_ = lcss[i][j - 1].length_;
						lcss[i][j].s_ = lcss[i][j - 1].s_;
					}
					else {
                        lcss[i][j].length_ = lcss[i - 1][j].length_;
						lcss[i][j].s_ = min(lcss[i - 1][j].s_, lcss[i][j - 1].s_);
					}
				}
			}
		}
		int max_length = lcss[length][length].length_, i = max_length / 2, j = max_length - i;
		const char* p = lcss[length][length].s_.c_str();
		copy(p, p + i, s);
		reverse_copy(p, p + j, s + i);
		s[i + j ] = '\0';
		printf("%s\n", s);
	}
	return 0;
}

