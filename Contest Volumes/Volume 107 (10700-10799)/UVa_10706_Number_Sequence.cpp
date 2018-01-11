
/*
	UVa 10706 - Number Sequence

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10706_Number_Sequence.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
	Let nr_digits(k) be the number of digits for S(k), then:
		nr_digits(1) = 1
		nr_digits(k) = nr_digits(k - 1) + log10(k) + 1 for k > 1
*/

const int nr_s_digits_max = 32768;
vector<unsigned int> nr_s_digits(nr_s_digits_max);
	// nr_s_digits[k] is the number of digits for the sequence of number groups S(1)S(2)...S(k)

int main()
{
	// generate nr_s_digits
	int nr_s = 0;
	unsigned int nr_digits = 0;
	nr_s_digits[nr_s++] = nr_digits;
	do {
		nr_digits += static_cast<unsigned int>(floor(log10(static_cast<double>(nr_s)))) + 1;
		nr_s_digits[nr_s] = nr_s_digits[nr_s - 1] + nr_digits;
	} while (nr_s_digits[nr_s++] < 2147483647);

	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		unsigned int p;
		cin >> p;
		vector<unsigned int>::const_iterator i = lower_bound(nr_s_digits.begin(), nr_s_digits.begin() + nr_s, p);
		--i;
		unsigned int q = *i;
		nr_digits = 0;
		unsigned int n;
		for (n = 1; ; n++) { // find the number in which p resides
			nr_digits += static_cast<unsigned int>(floor(log10(static_cast<double>(n)))) + 1;
			if (q + nr_digits >= p)
				break; // p points to one digit in n
		}
		unsigned int digit;
		for ( ; ; n /= 10, nr_digits--) {
			digit = n % 10;
			if (q + nr_digits == p)
				break;
		}
		cout << digit << endl;
	}

	return 0;
}

