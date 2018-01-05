
/*
	UVa 10148 - Advertisement

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10148_Advertisement.cpp

	This is another accepted solution, Time = 0.010, Rank = 2.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int N_max = 1000, number_min = -10000, number_max = 10000;
bool numbers[number_max - number_min + 1];

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
		int l_min = number_max - number_min + 1;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &paths[i].l_, &paths[i].h_);
			paths[i].l_ -= number_min, paths[i].h_ -= number_min;
			if (paths[i].l_ > paths[i].h_)
				swap(paths[i].l_, paths[i].h_);
			l_min = min(l_min, paths[i].l_);
		}
		sort(paths, paths + N);
		int nr_numbers = 0;
		memset(numbers, 0, sizeof(numbers));
		for (int i = 0; i < N; i++) {
			const path& p = paths[i];
			if (p.h_ - p.l_ < K) {
				for (int j = p.l_; j <= p.h_; j++) {
					if (!numbers[j])
						nr_numbers++;
					numbers[j] = true;
				}
			}
			else {
				int k = K;
				for (int j = p.l_; j <= p.h_ && k; j++)
					if (numbers[j])
						k--;
				if (k) {
					for (int j = p.h_; j >= p.l_ && k; j--)
						if (!numbers[j])
							nr_numbers++, numbers[j] = true, k--;
				}
			}
		}
		printf("%d\n", nr_numbers);
		for (int i = l_min; i <= paths[N - 1].h_ && nr_numbers; i++)
			if (numbers[i]) {
				printf("%d\n", i + number_min);
				nr_numbers--;
			}
		if (nr_cases)
			putchar('\n');
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

