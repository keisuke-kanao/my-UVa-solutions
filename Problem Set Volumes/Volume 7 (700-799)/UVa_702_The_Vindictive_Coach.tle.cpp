
/*
	UVa 702 - The Vindictive Coach

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_702_The_Vindictive_Coach.cpp

	This solution has never been submitted, but if it were, it would be verdicted TLE.
*/

#include <vector>
#include <map>
#include <cstdio>
using namespace std;

const int N_max = 22;

map<pair<int, int>, long long> nr_alignments[N_max];

int main()
{
	int N, m;
	while (scanf("%d %d", &N, &m) != EOF) {
		if (N == 1) {
			puts("1");
			continue;
		}
		m--;
		int n = 0, less;
		if (!m) {
			n++;
			m = (N > 2) ? 2 /* the thirt shortest player */ : 1 /* the second shortest player */;
			nr_alignments[n].clear();
			nr_alignments[n].insert(make_pair(make_pair(1 | (1 << m), m), 1));
		}
		else {
			nr_alignments[n].clear();
			nr_alignments[n].insert(make_pair(make_pair(1 << m, m), 1));
		}
		for (n++, less = 1; n < N; n++, less = 1 - less) {
			nr_alignments[n].clear();
			for (map<pair<int, int>, long long>::const_iterator i = nr_alignments[n - 1].begin(); i != nr_alignments[n - 1].end(); ++i) {
				int players = i->first.first, pp = i->first.second;
				long long nr = i->second;
				for (int p = 0, pb = 1; p < N; p++, pb <<= 1)
					if ((players & pb) == 0 & (less && pp > p || !less && pp < p)) {
						pair<map<pair<int, int>, long long>::iterator, bool> result = nr_alignments[n].insert(make_pair(make_pair(players | pb, p), nr));
						if (!result.second)
							result.first->second += nr;
					}
			}
#ifdef DEBUG
			printf("%d\n  ", nr_alignments[n].size());
			for (map<pair<int, int>, long long>::const_iterator i = nr_alignments[n].begin(); i != nr_alignments[n].end(); ++i)
				printf("[%06x %2d]:%lld ", i->first.first, i->first.second, i->second);
			putchar('\n');
#endif
		}
		int players = (1 << N) - 1;
		long long nr = 0;
		for (map<pair<int, int>, long long>::const_iterator i = nr_alignments[N - 1].begin(); i != nr_alignments[N - 1].end(); ++i)
			if (i->first.first == players)
				nr += i->second;
		printf("%lld\n", nr);
	}
	return 0;
}

