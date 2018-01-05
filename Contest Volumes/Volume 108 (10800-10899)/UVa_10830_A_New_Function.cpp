
/*
	UVa 10830 - A New Function

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10830_A_New_Function.cpp
*/

#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int case_nr = 1; ; case_nr++) {
		long long n;
		scanf("%lld", &n);
		if (!n)
			break;
		long long csod = 0;
		for (int i = 2; i <= n / i; i++)
			csod += i * (n / i - 1) ;
		for (int i = 2; i < n / i; i++) {
			long long l = n / (i + 1) + 1, r = n / i ;
			if (l > i)
				csod += (l + r) * (r - l + 1) / 2 * ( i - 1) ;
		}
		printf("Case %d: %lld\n", case_nr, csod);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

/*
int main() // first version, TLE
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int case_nr = 1; ; case_nr++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		long long csod = 0;
		if (n > 3)
	 		for (int i = 2; ; i++) {
				int d = n / i;
				if (d == 1)
					break;
				csod += i * (d - 1);
			}
		printf("Case %d: %lld\n", case_nr, csod);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}
*/

