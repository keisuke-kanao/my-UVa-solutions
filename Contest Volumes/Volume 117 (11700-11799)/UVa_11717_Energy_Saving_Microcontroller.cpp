
/*
	UVa 11717 - Energy Saving Microcontroller

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11717_Energy_Saving_Microcontroller.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n, i, k;
		scanf("%d %d %d", &n, &i, &k);
		bool active = true;
		int nr_inactive = 0, nr_ignored = 0, last_active = 0, next_active;
		while (n--) {
			int ms;
			scanf("%d", &ms);
			if (active) {
				if (ms < last_active + i)
					last_active = ms;
				else {
					active = false;
					nr_inactive++;
					next_active = ms + k;
				}
			}
			else {
				if (ms < next_active)
					nr_ignored++;
				else if (ms < next_active + i) {
					active = true;
					last_active = ms;
				}
				else {
					nr_inactive++;
					next_active = ms + k;
				}
			}
		}
		printf("Case %d: %d %d\n", t, nr_inactive, nr_ignored);
	}
	return 0;
}

