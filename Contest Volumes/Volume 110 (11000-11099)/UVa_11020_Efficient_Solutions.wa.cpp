
/*
	UVa 11020 - Efficient Solutions

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11020_Efficient_Solutions.cpp

	This solution was verdicted Wrong Answer.
*/

#include <algorithm>
#ifdef DEBUG
#include <iterator>
#endif
#include <vector>
#include <cstdio>
using namespace std;

const int n_max = 15000;

struct groom {
	int lineage_, charm_;

	groom() {}
	groom(int l, int c) : lineage_(l), charm_(c) {}
	groom(const groom& g) : lineage_(g.lineage_), charm_(g.charm_) {}

	bool dominate(const groom& g) const {
		return lineage_ < g.lineage_ && charm_ <= g.charm_ || lineage_ <= g.lineage_ && charm_ < g.charm_;
	}
	bool operator<(const groom& g) const {
		return dominate(g);
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
		if (n) {
			vector<groom> grooms;
			groom g;
			scanf("%d %d", &g.lineage_, &g.charm_);
			grooms.push_back(g);
			printf("%u\n", grooms.size());
			while (--n) {
				scanf("%d %d", &g.lineage_, &g.charm_);
				vector<groom>::iterator gi = upper_bound(grooms.begin(), grooms.end(), g);
				if (gi == grooms.end()) {
					for (gi = grooms.begin(); gi != grooms.end(); ++gi)
						if (g.dominate(*gi)) {
#ifdef DEBUG
							printf("%u: (%d %d)\n", distance(grooms.begin(), gi), gi->lineage_, gi->charm_);
#endif
							*gi = g;
							break;
						}
					if (gi == grooms.end()) {
#ifdef DEBUG
						printf("%u:\n", distance(grooms.begin(), gi));
#endif
						if (!grooms.back().dominate(g))
							grooms.push_back(g);
					}
				}
				else {
#ifdef DEBUG
					printf("%u: (%d %d)\n", distance(grooms.begin(), gi), gi->lineage_, gi->charm_);
#endif
					if (g.dominate(*gi)) {
						*gi++ = g;
						grooms.erase(gi, grooms.end());
					}
				}
#ifdef DEBUG
				for (vector<groom>::const_iterator i = grooms.begin(); i != grooms.end(); ++i)
					printf("(%d %d) ", i->lineage_, i->charm_);
				putchar('\n');
#endif
				printf("%u\n", grooms.size());
			}
		}
		if (cn < N)
			putchar('\n');
	}
	return 0;
}

