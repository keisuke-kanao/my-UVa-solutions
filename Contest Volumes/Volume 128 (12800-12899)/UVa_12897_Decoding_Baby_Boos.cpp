
/*
	UVa 12897 - Decoding Baby Boos

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12897_Decoding_Baby_Boos.cpp
*/

#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

const int nr_chars_max = 1000000;
char S[nr_chars_max + 1];

const int nr_letters = 'Z' - 'A' + 1;

struct rule {
	int i_; // ordinal # at which this rule is defined
	int r_; // this rule reverse replaces a charecter with ('A' + r_)

	rule() {}
	rule(int i, int r) : i_(i), r_(r) {}

	bool operator<(const rule& r) const {return i_ < r.i_;}
};

vector<rule> rules[nr_letters];
char replaces[nr_letters]; // replaces[i] is the reverse replacement of ('A' + i)

char replace(int s)
{
	if (rules[s].empty())
		return 'A' + s;
	rule r = rules[s].front();
	while (true) {
		const vector<rule>& rs = rules[r.r_];
		vector<rule>::const_iterator i = upper_bound(rs.begin(), rs.end(), r);
		if (i == rs.end())
			break;
		r = *i;
/*
		size_t i;
		for (i = 0; i < rs.size(); i++)
			if (rs[i].i_ > r.i_)
				break;
		if (i == rs.size())
			break;
		r = rs[i];
*/
	}
	return 'A' + r.r_;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", S);
		int R;
		scanf("%d", &R);
		for (int i = 0; i < R; i++) {
			char ai[2], bi[2];
			scanf("%s %s", ai, bi);
			rules[bi[0] - 'A'].push_back(rule(i, ai[0] - 'A'));
		}
		for (int i = 0; i < nr_letters; i++)
			sort(rules[i].begin(), rules[i].end());
		for (int i = 0; i < nr_letters; i++)
			replaces[i] = replace(i);
		for (char* p = S; *p; p++)
			if (*p != '_')
				*p = replaces[*p - 'A'];
		puts(S);
		if (T)
			for (int i = 0; i < nr_letters; i++)
				rules[i].clear();
	}
	return 0;
}

