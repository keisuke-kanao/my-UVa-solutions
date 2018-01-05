
/*
	UVa 10339 - Watching Watches

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10339_Watching_Watches.cpp
*/

#include <cstdio>
#include <cstdlib>

int main()
{
	int k, m;
	while (scanf("%d %d", &k, &m) != EOF) {
		int d = abs(k - m);
		long long minutes;
		if (!d)
			minutes = 1;
		else {
			minutes = ((86400LL - k) * 43200) / (60 * d);
			long long a = (86400LL - k) * 43200, b = 60LL * d;
        	if ((a % b) * 2 >= b)
				minutes++;
		}
   	    long long hr = (minutes / 60) % 12, mn = minutes % 60;
		if (!hr)
			hr = 12;
        printf("%d %d %02lld:%02lld\n", k, m, hr, mn);
	}
	return 0;
}

