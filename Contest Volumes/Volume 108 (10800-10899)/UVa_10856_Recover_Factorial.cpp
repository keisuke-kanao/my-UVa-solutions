
/*
	UVa 10856 - Recover Factorial

	To build using Visual Studio 2012
		cl -EHsc -O2 UVa_10856_Recover_Factorial.cpp

	An accepted solution, run time = 0.712 sec, ranking = 235.
*/

#include <cstdio>
#include <cstdlib>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int n_max = 2703663 /* 10000001 */;
int nr_pfs[n_max + 1]; // nr_pfs[i] is the nmber of prime factors of i
int total_nr_pfs[n_max + 1]; // total_nr_pfs[i] is the total number of prime factors up to i

int compare_int(const void* i, const void* j)
{
	return *reinterpret_cast<const int*>(i) - *reinterpret_cast<const int*>(j);
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	nr_pfs[2] = 1;
	for (long long i = 2; i * 2 <= n_max; i++)
		nr_pfs[i * 2] = nr_pfs[i] + 1;
	for (long long i = 3; i <= n_max; i += 2) {
		if (!nr_pfs[i])
			nr_pfs[i] = 1;
		for (long long j = 2; i * j <= n_max; j++)
			nr_pfs[i * j] = nr_pfs[i] + nr_pfs[j];
	}
	for (int i = 2; i <= n_max; i++) {
		total_nr_pfs[i] = total_nr_pfs[i - 1] + nr_pfs[i];
#ifdef DEBUG
		printf("%d: %d %d\n", i, nr_pfs[i], total_nr_pfs[i]);
#endif
	}
#ifdef DEBUG
	printf("%d\n", total_nr_pfs[n_max]);
#endif
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif

	for (int tc = 1; ; tc++) {
		int n;
		scanf("%d", &n);
		if (n < 0)
			break;
		printf("Case %d: ", tc);
		int* pi = total_nr_pfs;
		if (n)
			pi = reinterpret_cast<int*>(bsearch(&n, total_nr_pfs, n_max + 1, sizeof(int), compare_int));
		if (pi)
			printf("%d!\n", pi - total_nr_pfs);
		else
			puts("Not possible.");
	}
	return 0;
}

