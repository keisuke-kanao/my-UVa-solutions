
/*
	UVa 10916 - Factstone Benchmark

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10916_Factstone_Benchmark.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	For pow(2, i) >= n!, taking the logarithm (base 2) of both sides results in:
		i >= log2(n) + log2(n - 1) + log2(n - 3) + ... + log2(2) + log2(1).
*/

int main()
{
	const int first_year = 1960, last_year = 2160;
	const int nr_factstones = (last_year - first_year) / 10 + 1;
	int factstones[nr_factstones];
	const double log2 = log10(2.0);
	double nr_bits = 4.0, n = 3, factorial = 1.0;
	for (int i = 0; i < nr_factstones; i++, nr_bits *= 2.0) {
		do
			factorial += log10(static_cast<double>(n++)) / log2;
		while (factorial <= nr_bits);
		factstones[i] = n - 2;
#ifdef DEBUG
		cout << first_year + i * 10 << ' ' << factstones[i] << endl;
#endif
	}
	while (true) {
		int year;
		cin >> year;
		if (!year)
			break;
		cout << factstones[(year - first_year) / 10] << endl;
	}
	return 0;
}

