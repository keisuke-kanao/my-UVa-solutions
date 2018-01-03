
/*
	UVa 1047 - Zones

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1047_Zones.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_towers_max = 20, nr_csas_max = 10;

int nr_customers[nr_towers_max];

struct csa { // common service area
	int nr_towers_;
	unsigned int towers_;
	int nr_customers_;
} csas[nr_csas_max];

int nr_planned, nr_built, nr_csas, max_nr_customers;
unsigned int max_towers;

void build_towers(int n, int ti, unsigned int towers)
{
	unsigned int t;
	if (n == nr_built) {
		int nc = 0;
		t = towers;
		for (int i = 0; t; i++, t >>= 1)
			if (t & 1)
				nc += nr_customers[i];
		for (int i = 0; i < nr_csas; i++) {
			const csa& c = csas[i];
			t = towers & c.towers_;
			if (t) {
				int nt = 0;
				for (unsigned int tt = t; tt; tt >>= 1)
					if (tt & 1)
						nt++;
				nc -= (min(nt, c.nr_towers_) - 1) * c.nr_customers_;
			}
		}
#ifdef DEBUG
		printf("%d %#x\n", nc, towers);
#endif
		if (nc > max_nr_customers) {
			max_nr_customers = nc;
			max_towers = towers;
		}
	}
	else if (ti < nr_planned) {
		t = 1 << ti;
		towers |= t;
		build_towers(n + 1, ti + 1, towers);
		towers &= ~t;
		build_towers(n, ti + 1, towers);
	}
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		scanf("%d %d", &nr_planned, &nr_built);
		if (!nr_planned && !nr_built)
			break;
		for (int i = 0; i < nr_planned; i++)
			scanf("%d", &nr_customers[i]);
		scanf("%d", &nr_csas);
		for (int i = 0; i < nr_csas; i++) {
			csa& c = csas[i];
			scanf("%d", &c.nr_towers_);
			c.towers_ = 0;
			for (int j = 0; j < c.nr_towers_; j++) {
				int k;
				scanf("%d", &k);
				c.towers_ |= 1 << (k - 1);
			}
			scanf("%d", &c.nr_customers_);
		}
		max_nr_customers = 0;
		build_towers(0, 0, 0);
		printf("Case Number  %d\nNumber of Customers: %d\n", case_nr, max_nr_customers);
		printf("Locations recommended:");
		for (int i = 1; max_towers; i++, max_towers >>= 1)
			if (max_towers & 1)
				printf(" %d", i);
		printf("\n\n");
	}
	return 0;
}

