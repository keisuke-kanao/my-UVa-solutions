
/*
	UVa 11516 - WiFi

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11516_WiFi.cpp

	This solution was verdicted as Wrong Answer.
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
		for (int i = 0; i < m; i++)
			scanf("%d", &houses[i]);
		if (n >= m) {
			printf("%.1lf\n", 0.0);
			continue;
		}
		sort(houses, houses + m);
		int low = houses[0], high = houses[m - 1], mid;
		while (low <= high) {
			mid = (low + high) / 2;
			int n0 = 1, n1 = 1;
			for (int i = 1, s0 = houses[0], s1 = houses[0]; i < m; i++) {
				if (houses[i] - s0 > mid) {
					if (++n0 > n)
						break;
					s0 = houses[i];
				}
				if (houses[i] - s1 > mid - 1) {
					n1++;
					s1 = houses[i];
				}
			}
#ifdef DEBUG
			printf("low: %d, high: %d mid: %d, n0: %d n1: %d\n", low, high, mid, n0, n1);
#endif
			if (n0 > n) // houses cannot be covered with the interval of mid
				low = mid + 1;
			else if (n1 > n) // houses cannot be covered with the interval of (mid - 1)
				break;
			else
				high = mid - 1;
		}
		printf("%.1lf\n", mid / 2.0);
	}
	return 0;
}

