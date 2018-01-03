
/*
	UVa 636 - Squares (III)

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_636_Squares_III.cpp
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

long long convert_number(const string& number, int base)
{
	long long n = 0;
	for (size_t i = 0, j = number.length(); i < j; i++) {
		int k = number[i] - '0';
		if (k >= base)
			return -1;
		n *= base;
		n += k;
	}
	return n;
}

int main()
{
	const int base_max = 100;
	while (true) {
		string number;
		cin >> number;
		if (number == "0")
			break;
		int base;
		for (base = 2; base <= base_max; base++) {
			long long n = convert_number(number, base);
			if (n != -1) {
				long long sqrt_n = static_cast<long long>(sqrt(static_cast<double>(n)));
				if (sqrt_n * sqrt_n == n)
					break;
			}
		}
		cout << base << endl;
	}
	return 0;
}

