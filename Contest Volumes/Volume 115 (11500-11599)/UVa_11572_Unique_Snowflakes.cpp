
/*
	UVa 11572 - Unique Snowflakes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11572_Unique_Snowflakes.cpp

	from Waterloo ACM Programming Contest February 8, 2009, Problem A
		(http://acm.student.cs.uwaterloo.ca/~acm00/090208/data/)
*/

#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		int ci = 0, pi = 0, max_sf = 0;
		map<int, int> sf;
		for ( ; ci < n; ci++) {
			int s;
			scanf("%d", &s);
			pair<map<int, int>::iterator, bool> result = sf.insert(make_pair(s, ci));
			if (!result.second) {
				if (result.first->second >= pi) {
					max_sf = max(max_sf, ci - pi);
					pi = result.first->second + 1;
				}
				result.first->second = ci;
			}
		}
		max_sf = max(max_sf, ci - pi);
		printf("%d\n", max_sf);
	}
	return 0;
}

