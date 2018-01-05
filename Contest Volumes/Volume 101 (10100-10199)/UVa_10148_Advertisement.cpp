
/*
	UVa 10148 - Advertisement

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10148_Advertisement.cpp

	This is an accepted solution, Time = 0.210, Rank = 182.
*/

/*
You can solve it using a greedy strategy.
Sort the intervals by non-decreasing end.
For each interval, if the length is <= K then put a billboard at every location.
Otherwise place billboards at the largest unused location within that interval 
until at least K billboards have been placed inside it.
*/

#include <algorithm>
#include <vector>
#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int N_max = 1000, number_min = -10000, number_max = 10000;
int numbers[number_max - number_min + 1];

struct path {
	int l_, h_;

	bool operator<(const path& p) const {return h_ < p.h_;}
} paths[N_max];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int K, N;
		scanf("%d %d", &K, &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &paths[i].l_, &paths[i].h_);
			if (paths[i].l_ > paths[i].h_)
				swap(paths[i].l_, paths[i].h_);
		}
		sort(paths, paths + N);
		int nr_numbers = 0;
		for (int i = 0; i < N; i++) {
			const path& p = paths[i];
			int j, nr = 0;
			if (p.h_ - p.l_ < K) {
				for (j = p.l_; j <= p.h_; j++)
					if (!binary_search(numbers, numbers + nr_numbers, j))
						numbers[nr_numbers + nr++] = j;
			}
			else {
				j = lower_bound(numbers, numbers + nr_numbers, p.l_) - numbers;
				int k = K - (nr_numbers - j);
				for (j = p.h_; j >= p.l_ && k > 0; j--)
					if (!binary_search(numbers, numbers + nr_numbers, j))
						numbers[nr_numbers + nr++] = j, k--;
			}
			if (nr) {
				nr_numbers += nr;
				sort(numbers, numbers + nr_numbers);
			}
		}
		printf("%d\n", nr_numbers);
		for (int i = 0; i < nr_numbers; i++)
			printf("%d\n", numbers[i]);
		if (nr_cases)
			putchar('\n');
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

