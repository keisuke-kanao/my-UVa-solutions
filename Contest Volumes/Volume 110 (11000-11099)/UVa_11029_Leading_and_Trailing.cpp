
/*
	UVa 11029 - Leading and Trailing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11029_Leading_and_Trailing.cpp

	An accepted solution.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int leading(int n, int k)
{
/*
	n^k = 10^(k * logn)
	decimal part of n^k = 10^(decimal part of k * log(n))
*/
	double k_log_n = static_cast<double>(k) * log10(static_cast<double>(n));
	double decimal_part_of_k_log_n = k_log_n - floor(k_log_n);
	double decimal_part = pow(10.0, decimal_part_of_k_log_n);
	return static_cast<int>(decimal_part * 100.0);
}

long long trailing(int n, int k)
{
	if (!k)
		return 1;
	long long t = trailing(n, k / 2);
	t = (t * t) % 1000;
	if (k & 1) // k is odd
		t = (t * n) % 1000;
	return t;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (nr_cases--) {
		int n, k;
		cin >> n >> k;
		cout << leading(n, k) << "..." << setfill('0') << setw(3) << trailing(n, k) << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

