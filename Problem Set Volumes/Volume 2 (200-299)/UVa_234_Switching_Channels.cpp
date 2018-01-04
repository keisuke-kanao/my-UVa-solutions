
/*
	UVa 234 - Switching Channels

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_234_Switching_Channels.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int p_max = 8, a_max = 8, il_max = 5;

int programs[p_max];

struct alignment_point {
	int il_, t_;
} alignment_points[a_max];

int main()
{
	for (int ds = 1; ; ds++) {
		int p, a;
		scanf("%d", &p);
		if (!p)
			break;
		for (int i = 0; i < p; i++)
			scanf("%d", &programs[i]);
		scanf("%d", &a);
		int il = 0; // inportance level
		for (int i = 0; i < a; i++) {
			scanf("%d %d", &alignment_points[i].il_, &alignment_points[i].t_);
			il = max(il, alignment_points[i].il_);
		}
		sort(programs, programs + p);
		int min_err = -1, min_programs[p_max], min_miss_times[il_max + 1];
		do {
			int tm = 0, times[p_max + 1], miss_times[il_max + 1], err = 0;
			for (int i = 0; i < p; i++) {
				times[i] = tm;
				tm += programs[i];
			}
			times[p] = tm;
			memset(miss_times, 0, sizeof(miss_times));
			for (int i = 0; i < a; i++) {
				int t = alignment_points[i].t_, il = alignment_points[i].il_, mt = numeric_limits<int>::max();
				for (int j = 0; j <= p; j++)
					mt = min(mt, abs(times[j] - t));
				miss_times[il] += mt;
				err += mt;
			}
#ifdef DEBUG
				for (int i = 0; i < p; i++)
					printf("%d%c", programs[i], ((i < p - 1) ? ' ' : ':'));
				putchar(' ');
				for (int i = 1; i <= il; i++)
					printf("%d%c", miss_times[i], ((i < il) ? ' ' : ':'));
				printf(" %d", err);
#endif
			bool better = false;
			if (min_err == -1)
				better = true;
			else {
				for (int i = 1; i <= il; i++) {
					if (miss_times[i] < min_miss_times[i]) {
						better = true; break;
					}
					else if (miss_times[i] > min_miss_times[i])
						break;
				}
			}
#ifdef DEBUG
			puts((better) ? " better" : "");
#endif
			if (better) {
				min_err = err;
				memcpy(min_programs, programs, sizeof(int) * p);
				memcpy(min_miss_times, miss_times, sizeof(int) * (il + 1));
#ifndef DEBUG
				if (!min_err)
					break;
#endif
			}
		} while (next_permutation(programs, programs + p));
		printf("Data set %d\n", ds);
		printf("Order: ");
		for (int i = 0; i < p; i++)
			printf("%d%c", min_programs[i], ((i < p - 1) ? ' ' : '\n'));
		printf("Error: %d\n", min_err);
/*
			printf("Data set %d\n", ds);
		printf("  Order: ");
		for (int i = 0; i < p; i++)
			printf("%d%c", min_programs[i], ((i < p - 1) ? ' ' : '\n'));
		printf("  Error: %d\n", min_err);
*/
	}
	return 0;
}

