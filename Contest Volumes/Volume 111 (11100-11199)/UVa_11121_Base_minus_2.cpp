
/*
	UVa 11121 - Base -2

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11121_Base_minus_2.cpp
*/

#include <iostream>
using namespace std;

const int nr_bits = 32;

long long positive_max_values[nr_bits / 2] = {
	0x1, 0x5, 0x15, 0x55, 0x155, 0x555, 0x1555, 0x5555, 0x15555, 0x55555,
	0x155555, 0x555555, 0x1555555, 0x5555555, 0x15555555, 0x55555555
};
	// positive_max_values[i] is the max. value that a positive integer can take with (2 * i + 1)-bits
	// (or MSB of (2 * i) bit)

long long negative_max_values[nr_bits] = {
	0x2, 0xa, 0x2a, 0xaa, 0x2aa, 0xaaa, 0x2aaa, 0xaaaa, 0x2aaaa, 0xaaaaa,
   0x2aaaaa, 0xaaaaaa, 0x2aaaaaa, 0xaaaaaaa, 0x2aaaaaaa, 0xaaaaaaaa
};
	// negative_max_values[i] is the max. vaolue that the absolue value of a negative integer can take 
	// with (2 * (i + 1))-bits (or MSB of (2 * i + 1) bit)

int binary_search_max_value(long long i, const long long max_values[])
{
	int l = 0, h = nr_bits / 2 - 1, m;
	while (l <= h) {
		m = l + (h - l) / 2;
		if (max_values[m] == i)
			return m;
		else if (max_values[m] < i)
			l = m + 1;
		else
			h = m - 1;
	}
	return l;
}

long long base_minus_two(long long n)
{
	if (!n)
		return 0;
	int i;
	long long rep;
	if (n > 0) {
		i = binary_search_max_value(n, positive_max_values) * 2;
		rep = static_cast<long long>(1) << i;
		return rep | base_minus_two(n - rep);
	}
	else {
		i = binary_search_max_value(-n, negative_max_values) * 2 + 1;
		rep = static_cast<long long>(1) << i;
		return rep | base_minus_two(n + rep);
	}
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	for (int c = 1; c <= nr_cases; c++) {
		int n;
		cin >> n;
		long long rep = base_minus_two(n);
		cout << "Case #" << c << ": ";
		long long b = static_cast<long long>(1) << (nr_bits - 1);
		int i;
		for (i = 0; i < nr_bits; i++, b >>= 1)
			if (rep & b)
				break;
		if (i == nr_bits)
			cout << 0;
		else {
			for ( ; i < nr_bits; i++, b >>= 1)
				cout << ((rep & b) ? '1' : '0');
		}
		cout << endl;
	}
	return 0;
}

