
/*
	UVa 11958 - Coming Home

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11958_Coming_Home.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	int t;
	scanf("%d", &t);
	for (int cn = 1; cn <= t; cn++) {
		int k, hh, mm, q, ct, t, min_minutes;
		scanf("%d %d:%d", &k , &hh, &mm);
		ct = hh * 60 + mm;
		for (int i = 0; i < k; i++) {
			scanf("%d:%d %d", &hh, &mm, &q);
			t = hh * 60 + mm;
			if (t < ct)
				t += 24 * 60;
			if (i)
				min_minutes = min(min_minutes, t - ct + q);
			else
				min_minutes = t - ct + q;
		}
		printf("Case %d: %d\n", cn, min_minutes);
	}
	return 0;
}

