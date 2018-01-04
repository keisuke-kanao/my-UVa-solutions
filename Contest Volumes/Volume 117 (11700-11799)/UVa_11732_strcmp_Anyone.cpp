
/*
	UVa 11732 - "strcmp()" Anyone?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11732_strcmp_Anyone.cpp
*/

/*
There is a simple way to solve this problem without using any sophisticated string algorithms.

-> Sort all strings in O(n*max(length of string) * log(n)).
-> For each pair of consecutive strings (once sorted) compute the longest common prefix with the naive algorithm.
-> Having this information you can compute the result in O(n^2).

It's not very efficient but it passes.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N_max = 4000, nr_chars_max = 1000;

struct string {
	char s_[nr_chars_max + 1];

	bool operator<(const string& s) const {return strcmp(s_, s.s_) < 0;}
} strings[N_max];

int nr_comparisons[N_max];
	// nr_comparisons[i] is the number of comparisons between strings[i] and strings[i + 1]

int main()
{
	for (int c = 1; ; c++) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++)
			scanf("%s", strings[i].s_);
		sort(strings, strings + N);
		for (int i = 0; i < N - 1; i++) {
			const char *cs = strings[i].s_, *ns = strings[i + 1].s_;
			int nr = 1;
			for ( ; *cs == *ns; nr++, cs++, ns++) {
				nr++;
				if (!*cs)
					break;
			}
			nr_comparisons[i] = nr;
		}
		long long T = 0;
		for (int i = 0; i < N - 1; i++) {
			int nr = nr_comparisons[i];
			T += nr;
			for (int j = i + 1; j < N - 1; j++) {
				if (nr_comparisons[j] < nr)
					nr = nr_comparisons[j];
				T += nr;
			}
		}
		printf("Case %d: %lld\n", c, T);
	}
	return 0;
}

