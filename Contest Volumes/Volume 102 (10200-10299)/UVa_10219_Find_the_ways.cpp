
/*
	UVa 10219 - Find the ways !

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10219_Find_the_ways.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	number of digits = floor(log10(C(n, k))) + 1
	log10(C(n, k)) = log10(n! / (k! * (n - k)!)) = log10(n!) - log10(k!) - log10((n - k)!)
	log10(n!) = log10(1 * 2 * ... * (n - 1) * n) = log10(1) + log10(2) + ... + log10(n - 1) + log10(n)
*/

double log_of_factorial(long long s, long long e)
{
	double d = 0.0;
	for (long long i = s; i <= e; i++)
		d += log10(static_cast<double>(i));
	return d;
}

int main()
{
	long long n, k;
	while (cin >> n >> k) {
		int nr_digits;
		if (n == k)
			nr_digits = 1;
		else {
			if (k > n - k)
				nr_digits = static_cast<int>(floor(log_of_factorial(k + 1, n) - log_of_factorial(1, n - k))) + 1;
			else
				nr_digits = static_cast<int>(floor(log_of_factorial(n - k + 1, n) - log_of_factorial(1, k))) + 1;
		}
		cout << nr_digits << endl;
	}
	return 0;
}

/*
[n * (n-1) * ... * (k+1)] / [(n-k) * ... * 1]

OR

[n * (n-1) * ... * (n-k+1)] / [k * ... * 1]

If k is larger, use the first definition, and if n-k is larger, use the second one.
*/

