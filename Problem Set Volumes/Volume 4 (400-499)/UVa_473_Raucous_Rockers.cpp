
/*
	UVa 473 - Raucous Rockers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_473_Raucous_Rockers.cpp

	An accepted solution.
*/

#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int n, t, m;
		scanf("%d %d %d", &n, &t, &m);
		vector< vector<int> > songs(m + 1, vector<int>(t + 1, 0));
		for (int i = 1; i <= n; i++) {
			int length;
        	scanf("%d%*c", &length);
			for (int j = m; j >= 1; j--) {
				for (int k = t; k >= 1; k--) {
                	if (k < length)
						continue;
					songs[j][k] = max(songs[j][k], songs[j - 1][t] + 1);
	                songs[j][k] = max(songs[j][k], songs[j][k - length] + 1);
	            }
    	    }
		}
		printf("%d\n", songs[m][t]);
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

