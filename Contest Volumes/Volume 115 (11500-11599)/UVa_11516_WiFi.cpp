
/*
	UVa 11516 - WiFi

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11516_WiFi.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int m_max = 100000;
int houses[m_max];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			scanf("%d", &houses[i]);
			houses[i] *= 10;
		}
		if (n >= m) {
			printf("%.1lf\n", 0.0);
			continue;
		}
		sort(houses, houses + m);
		int min_d, low = 0, high = houses[m - 1] - houses[0];
		while (low <= high) {
			int mid = (low + high) / 2;
			int ctr = 1;
			for (int i = 1, e = mid + houses[0]; i < m; i++)
				if (houses[i] - e > mid) {
					if (++ctr > n)
						break;
					e = houses[i] + mid;
				}
			if (ctr > n)
				low = mid + 1;
			else {
				min_d = mid;
				high = mid - 1;
			}
		}
		printf("%d.%d\n", min_d / 10, min_d % 10);
	}
	return 0;
}

