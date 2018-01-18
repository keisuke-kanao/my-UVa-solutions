
/*
	5.9.3 The Archeologist's Dilemma
	PC/UVa IDs: 110503/701, Popularity: A, Success rate: low Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_701_Archeologists_Dilemma.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

/*
N*10^k <= 2^x and 2^x < (N + 1) * 10^k, k -- number of missed digits, so 
log2(N * 10^k) <= log2(2^x) and log2(2^x) < log2((N + 1) * 10^k) 
log2(N) + k * log2(10) <= x and x < log2(N + 1) + k * log2(10) 

log2(N) = log10(N) / log10(2), log2(10) = log10(10) / log10(2) = 1 / loga10(2)

With these "equations" and brute-forcing on k we can found x fast enough.
*/

inline double log2(double x)
{
	return log10(x) / log10(2.0);
}

int get_smallest_exponent(int n, int nr_digits)
{
	for (nr_digits++; ; nr_digits++) {
		double d = static_cast<double>(nr_digits) * log2(10.0);
		double min_d = log2(static_cast<double>(n)) + d, max_d = log2(static_cast<double>(n + 1)) + d;
		double min_e = ceil(min_d), max_e = floor(max_d);
		if(min_e == max_e)
			return static_cast<int>(min_e);
	}
}

int main(int /* argc */, char** /* argv */)
{
	string sn;
	while (cin >> sn) {
		int nr_digits = sn.length();
		istringstream iss(sn);
		int n;
		iss >> n;
		cout << get_smallest_exponent(n, nr_digits) << endl;
	}
	return 0;
}

