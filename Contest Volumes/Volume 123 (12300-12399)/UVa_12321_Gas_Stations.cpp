
/*
	UVa 12321 - Gas Stations

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12321_Gas_Stations.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int G_max = 10000;

struct coverage {
	int l_, h_; // coverage is from l_ to h_

bool operator<(const coverage& c) const {return (l_ != c.l_) ? l_ < c.l_ : h_ < c.h_;}
} coverages[G_max];

int main()
{
	while (true) {
		int L, G;
		scanf("%d %d", &L, &G);
		if (!L)
			break;
		for (int i = 0; i < G; i++) {
			int xi, ri;
			scanf("%d %d", &xi, &ri);
			coverages[i].l_ = max(xi - ri, 0), coverages[i].h_ = min(xi + ri, L);
		}
		sort(coverages, coverages + G); // sort the stations by thier lower ends
#ifdef DEBUG
		for (int i = 0; i < G; i++)
			printf("[%d %d]%c", coverages[i].l_, coverages[i].h_, ((i < G - 1) ? ' ' : '\n'));
#endif
		int i = 0, h = 0, l = 0, nr = 0;
		for ( ; l < L && i < G; i++) {
			// discard the stations whose lower end is covered by other station
			const coverage& c = coverages[i];
			if (c.l_ > l) {
				if (c.l_ <= h) {
					l = h, h = 0, nr++;
					if (l == L)
						break;
				}
				else
					break;
			}
			h = max(h, c.h_);
		}
		if (h)
			l = h, nr++;
		printf("%d\n", (l == L) ? G - nr : -1);
	}
	return 0;
}

*/


