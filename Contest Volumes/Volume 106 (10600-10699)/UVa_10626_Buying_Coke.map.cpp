
/*
	UVa 10626 - Buying Coke

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10626_Buying_Coke.cpp

	This solution has not been submitted yet but if it were, it would be verdicted as TLE.
*/

#include <iostream>
#include <map>
#include <algorithm>
#include <limits>
using namespace std;

struct coins {
	int n5_, n10_;

	coins() {}
	coins(int n5, int n10) : n5_(n5), n10_(n10) {}

	bool operator<(const coins& c) const {
		return (n5_ != c.n5_) ? n5_ < c.n5_ : n10_ < c.n10_;
	}
};

void insert_remaining(const coins& c, int ic, map<coins, int>& remaining)
{
	pair<map<coins, int>::iterator, bool> result = remaining.insert(make_pair(c, ic));
	if (!result.second && result.first->second > ic)
		result.first->second = ic;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int C, n1, n5, n10;
		cin >> C >> n1 >> n5 >> n10;
		int amount = n1 + n5 * 5 + n10 * 10;
		map<coins, int> remainings[2];
		insert_remaining(coins(n5, n10), 0, remainings[0]);
		for (int i = 1; i <= C; i++) {
			int ci = i % 2, pi = (i - 1) % 2;
			remainings[ci].clear();
			for (map<coins, int>::const_iterator ri = remainings[pi].begin(), re = remainings[pi].end();
				ri != re; ++ri) {
				const coins& c = ri->first;
				int ic = ri->second;
				n1 = amount - c.n5_ * 5 - c.n10_ * 10;
				if (n1 >= 8)
					insert_remaining(coins(c.n5_, c.n10_), ic + 8, remainings[ci]);
				if (n1 >= 3 && c.n5_ >= 1)
					insert_remaining(coins(c.n5_ - 1, c.n10_), ic + 4, remainings[ci]);
				if (c.n5_ >= 2)
					insert_remaining(coins(c.n5_ - 2, c.n10_), ic + 2, remainings[ci]);
				if (c.n10_ >= 1)
					insert_remaining(coins(c.n5_, c.n10_ - 1), ic + 1, remainings[ci]);
				if (n1 >= 3 && c.n10_ >= 1)
					insert_remaining(coins(c.n5_ + 1, c.n10_ - 1), ic + 4, remainings[ci]);
			}
		}
		int min_ic = numeric_limits<int>::max();
		for (map<coins,int>::const_iterator ri = remainings[C % 2].begin(), re = remainings[C % 2].end();
			ri != re; ++ri) {
			min_ic = min(min_ic, ri->second);
		}
		cout << min_ic << endl;
	}
	return 0;
}

