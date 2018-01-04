
/*
	UVa 11997 - K Smallest Sums

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11997_K_Smallest_Sums.cpp
*/

#include <algorithm>
#include <queue>
#include <cstdio>
using namespace std;

const int k_max = 750;
int s[k_max], sums[k_max];

struct pair_sum {
	int i_, s_;

	pair_sum(int i, int s) : i_(i), s_(s) {}
	bool operator<(const pair_sum& ps) const {
		if (s_ != ps.s_)
			return s_ > ps.s_;
		else
			return i_ > ps.i_;
	}
};

int main()
{
	int k;
	while (scanf("%d", &k) != EOF) {
		for (int j = 0; j < k; j++)
			scanf("%d",  &sums[j]);
		sort(sums, sums + k);
		for (int i = 1; i < k; i++) {
			for (int j = 0; j < k; j++)
				scanf("%d",  &s[j]);
			sort(s, s + k);
			priority_queue<pair_sum> pq;
			for (int j = 0; j < k; j++)
				pq.push(pair_sum(0, sums[j] + s[0]));
			for (int j = 0; ; ) {
				pair_sum ps = pq.top(); pq.pop();
				sums[j++] = ps.s_;
				if (j == k)
					break;
				if (ps.i_ < k - 1)
					pq.push(pair_sum(ps.i_ + 1, ps.s_ + s[ps.i_ + 1] - s[ps.i_]));
			}
		}
		for (int i = 0; i < k; i++)
			printf("%d%c", sums[i], ((i < k - 1) ? ' ' : '\n'));
	}
	return 0;
}

