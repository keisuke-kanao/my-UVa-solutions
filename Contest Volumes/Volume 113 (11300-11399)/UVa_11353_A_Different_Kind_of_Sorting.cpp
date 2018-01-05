
/*
	UVa 11353 - A Different Kind of Sorting

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11353_A_Different_Kind_of_Sorting.cpp

	See also 10856 - Recover Factorial.
*/

#include <algorithm>
#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 2000000;

struct number {
	int n_;
	int nr_pfs_; // nmber of prime factors of n_

	bool operator<(const number& n) const {
		if (nr_pfs_ != n.nr_pfs_)
			return nr_pfs_ < n.nr_pfs_;
		else
			return n_ < n.n_;
	}
} numbers[n_max + 1];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 1; i <= n_max; i++)
		numbers[i].n_ = i;
	numbers[1].nr_pfs_ = numbers[2].nr_pfs_ = 1;
	for (long long i = 2; i * 2 <= n_max; i++)
		numbers[i * 2].nr_pfs_ = numbers[i].nr_pfs_ + 1;
	for (long long i = 3; i <= n_max; i += 2) {
		if (!numbers[i].nr_pfs_)
			numbers[i].nr_pfs_ = 1;
		for (long long j = 2; i * j <= n_max; j++)
			numbers[i * j].nr_pfs_ = numbers[i].nr_pfs_ + numbers[j].nr_pfs_;
#ifdef DEBUG
		printf("%d: %d\n", i, numbers[i].nr_pfs_);
#endif
	}
	sort(numbers + 1, numbers + n_max + 1);
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	for (int cn = 1; ; cn++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		printf("Case %d: %d\n", cn, numbers[n].n_);
	}
	return 0;
}

