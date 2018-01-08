
/*
	UVa 10061 - How many zero's and how many digits ?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10061_How_many_zeros.cpp
*/

#include <iostream>
#include <limits>
#include <algorithm>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int how_many_zeros(int n, int b)
{
	int nr_occurrences_max = numeric_limits<int>::max();
	for (int i = 2; i <= b; i++) {
		int nr_occurrences_in_b = 0; // number of occurrences of i in b
		for ( ; !(b % i); b /= i)
			nr_occurrences_in_b++;
		if (!nr_occurrences_in_b)
			continue;
		int nr_occurrences_in_f = 0; // number of occurrences of i in n!
		for (int j = i; j <= n; j *= i)
			nr_occurrences_in_f += n / j;
/*
		for (int j = 2; j <= n; j++)
			for (int k = j; !(k % i); k /= i)
				nr_occurrences_in_f++;
*/
		nr_occurrences_max = min(nr_occurrences_max, nr_occurrences_in_f / nr_occurrences_in_b);
	}
	return nr_occurrences_max;
}

int how_many_digits(int n, int b)
{
	double f = 0.0;
	for (int i = 2; i <= n; i++)
		f += log10(static_cast<double>(i));
	f /= log10(static_cast<double>(b));
	return (f != 0.0) ? static_cast<int>(ceil(f + 1.0e-10)) : 1;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int n, b;
	while (cin >> n >> b) {
		if (n == 1)
			cout << 0 << ' ' << 1 << endl;
		else
			cout << how_many_zeros(n, b) << ' ' << how_many_digits(n, b) << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

