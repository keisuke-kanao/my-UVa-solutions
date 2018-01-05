
/*
	UVa 11348 - Exhibition

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11348_Exhibition.cpp
*/

#include <vector>
#include <map>
#include <set>
#include <cstdio>
using namespace std;

int main()
{
	int K;
	scanf("%d", &K);
	for (int k = 1; k <= K; k++) {
		int N;
		scanf("%d", &N);
		map< int, set<int> > stamps;
			// key is  the type of stamp, value is the indices of friends who own the stamp
		for (int i = 0; i < N; i++) {
			int M;
			scanf("%d", &M);
			while (M--) {
				int A;
				scanf("%d", &A);
				pair<map< int, set<int> >::iterator, bool> result = stamps.insert(make_pair(A, set<int>()));
				result.first->second.insert(i);
			}
		}
		int ctr = 0;
		vector<int> unique_stamp_ctrs(N, 0);
		for (map< int, set<int> >::const_iterator i = stamps.begin(), e = stamps.end(); i != e; ++i)
			if (i->second.size() == 1) {
				ctr++;
				unique_stamp_ctrs[*i->second.begin()]++;
			}
		printf("Case %d:", k);
		if (ctr)
			for (size_t i = 0; i < N; i++)
				printf(" %.6lf%%", (static_cast<double>(unique_stamp_ctrs[i]) * 100.0) / static_cast<double>(ctr));
		putchar('\n');
	}
	return 0;
}

