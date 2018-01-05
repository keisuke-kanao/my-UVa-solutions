
/*
	UVa 11020 - Efficient Solutions

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11020_Efficient_Solutions.cpp

	This is an accepted solution.
*/

/*
11020 - Efficient Solutions
Use the C++ STL Set to solve a problem. Each time a gentlemen arrives, put him into set according to the rule.
LB < LA and CB <= CA, or
LB <= LA and CB < CA. WHEN B precedes A.
Once you insert into the set , output the rank using the "distance" function.
*/

#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;

struct groom {
	int lineage_, charm_;
	groom() {}
	groom(int l, int c): lineage_(l), charm_(c) {}

	bool operator<(const groom& g) const {
		return (lineage_ != g.lineage_) ? lineage_ < g.lineage_ : charm_ < g.charm_;
	}
};

int main()
{
	int N;
	scanf("%d", &N);
	for (int cn = 1; cn <= N; cn++) {
		int n;
		scanf("%d", &n);
		printf("Case #%d:\n", cn);
		multiset<groom> grooms;
		while (n--) {
			groom g;
			scanf("%d %d", &g.lineage_, &g.charm_);
			multiset<groom>::iterator gi = grooms.lower_bound(g);
			if (gi == grooms.begin() || (--gi)->charm_ > g.charm_) {
				grooms.insert(g);
				gi = grooms.upper_bound(g);
				while (gi != grooms.end() && gi->charm_ >= g.charm_)
					grooms.erase(gi++);
			}
			printf("%u\n", grooms.size());
        }
		if (cn < N)
			putchar('\n');
	}
	return 0;
}

