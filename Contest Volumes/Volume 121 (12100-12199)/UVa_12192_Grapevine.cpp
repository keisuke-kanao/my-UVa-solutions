
/*
	UVa 12192 - Grapevine

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12192_Grapevine.cpp
*/

#include <algorithm>
#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int N_max = 500, M_max = 500;

int H[N_max][M_max];
struct {
	int l_, u_, s_;
} intervals[N_max];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int N, M;
		scanf("%d %d", &N, &M);
		if (!N)
			break;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				scanf("%d", &H[i][j]);
		int Q;
		scanf("%d", &Q);
		while (Q--) {
			int L, U;
			scanf("%d %d", &L, &U);
			for (int i = 0; i < N; i++) {
				int (&h)[M_max] = H[i];
				intervals[i].l_ = lower_bound(h, h + M, L) - h;
				intervals[i].u_ = upper_bound(h, h + M, U) - h;
				intervals[i].s_ = max(0, intervals[i].u_ - intervals[i].l_);
#ifdef DEBUG
				printf("[%d]:%d %d %d\n", i, intervals[i].l_, intervals[i].u_, intervals[i].s_);
#endif
			}
			int max_side = 0;
			for (int i = 0; i < N; i++) {
				if (intervals[i].s_ <= max_side)
					continue;
				int s = intervals[i].s_, j = i + 1, s_max = min(intervals[i].s_, N - i);
				if (s_max <= max_side)
					continue;
				for ( ; j < i + s_max; j++) {
					if (!intervals[j].s_ || intervals[i].l_ > intervals[j].u_ ||
						intervals[i].u_ < intervals[j].l_)
						break;
					s = min(intervals[i].u_, intervals[j].u_) - max(intervals[i].l_, intervals[j].l_);
					if (s <= max_side)
						break;
					max_side = max(max_side, min(j - i + 1, s));
				}
				max_side = max(max_side, min(j - i, s));
			}
			printf("%d\n", max_side);
		}
		puts("-");
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

