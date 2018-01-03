
/*
	UVa 1237 - Expert Enough?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1237_Expert_Enough.cpp

	This solution might be wrong even if it would not verdict as TLE.
*/

#include <algorithm>
#include <iterator>
#include <cstdio>
using namespace std;

const int D_max = 10000, nr_chars_max = 31;
char makers[D_max][nr_chars_max + 1];
struct price {
	int mi_; // index to makers[]
	int l_, h_; // lowest price, highest price
} prices[D_max];

bool compare_lowest_price(const price& i, const price& j)
{
	return i.l_ < j.l_;
}

bool compare_highest_price(const price& i, const price& j)
{
	return i.h_ < j.h_;
}

int AES(int D, int P)
{
	sort(prices, prices + D, compare_lowest_price);
	price p;
	p.l_ = p.h_ = P;
	int lpi = distance(prices, upper_bound(prices, prices + D, p, compare_lowest_price));
	if (lpi) {
		lpi--;
		if (lpi && P == prices[lpi].l_ && prices[lpi].l_ == prices[lpi - 1].l_)
			return -1;
	}
	else
		return -1;
	int mi = prices[lpi].mi_, d = lpi + 1;
	sort(prices, prices + d, compare_highest_price);
	int hpi = distance(prices, lower_bound(prices, prices + d, p, compare_highest_price));
	if (hpi < d) {
		if (hpi == d - 1 || prices[hpi].h_ != P || prices[hpi].h_ != prices[hpi + 1].h_)
			return (mi == prices[hpi].mi_) ? mi : -1;
		else
			return -1;
	}
	else
		return -1;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int D;
		scanf("%d", &D);
		for (int i = 0; i < D; i++) {
			prices[i].mi_ = i;
			scanf("%s %d %d", makers[i], &prices[i].l_, &prices[i].h_);
		}
		int Q;
		scanf("%d", &Q);
		while (Q--) {
			int P;
			scanf("%d", &P);
			int mi = AES(D, P);
			if (mi != -1)
				printf("%s\n", makers[mi]);
			else
				puts("UNDETERMINED");
		}
		if (T)
			putchar('\n');
	}
	return 0;
}

