
/*
	UVa 1587 - Box

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1587_Box.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_pallets = 6;

struct pallet {
	int w_, h_;

	bool operator<(const pallet& p) const {
		if (w_ != p.w_)
			return w_ < p.w_;
		else
			return h_ < p.h_;
	}
} pallets[nr_pallets];

bool possible()
{
	if (pallets[0].w_ != pallets[1].w_ || pallets[0].w_ != pallets[2].w_ || pallets[0].w_ != pallets[3].w_)
		return false;
	if (pallets[0].h_ != pallets[1].h_ || pallets[0].h_ != pallets[4].w_ || pallets[0].h_ != pallets[5].w_)
		return false;
	if (pallets[2].h_ != pallets[3].h_ || pallets[2].h_ != pallets[4].h_ || pallets[2].h_ != pallets[5].h_)
		return false;
	return true;
}

int main()
{
	while (scanf("%d %d", &pallets[0].w_, &pallets[0].h_) != EOF) {
		if (pallets[0].w_ > pallets[0].h_)
			swap(pallets[0].w_, pallets[0].h_);
		for (int i = 1; i < nr_pallets; i++) {
			scanf("%d %d", &pallets[i].w_, &pallets[i].h_);
			if (pallets[i].w_ > pallets[i].h_)
				swap(pallets[i].w_, pallets[i].h_);
		}
		sort(pallets, pallets + nr_pallets);
		puts(possible() ? "POSSIBLE" : "IMPOSSIBLE");
	}
	return 0;
}

