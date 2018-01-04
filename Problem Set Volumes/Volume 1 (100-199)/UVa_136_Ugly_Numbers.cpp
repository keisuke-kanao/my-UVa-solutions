
/*
	UVa 136 - Ugly Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_136_Ugly_Numbers.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

#ifdef DEBUG
bool is_ugly_number(int n)
{
	for ( ; !(n & 1); n >>= 1)
		;
	if (n == 1)
		return true;
	int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n)) + 1.0);
	while (i <= e) {
		if (!(n % i)) {
			n /= i;
			e = static_cast<long long>(sqrt(static_cast<double>(n)) + 1.0);
		}
		else {
			i += 2;
			if (i > 5)
				break;
		}
	}
	return (n == 3 || n == 5) ? true : false;
}
#endif

int main()
{
#ifdef DEBUG
	int n = 2, nr_ugly_numbers = 1;
	for ( ; ; n++)
		if (is_ugly_number(n)) {
			cout << n << ' ';
			if (++nr_ugly_numbers == 1500)
				break;
		}
	cout << "The 1500'th ugly number is " << n << ".\n" << endl;
#else
	cout << "The 1500'th ugly number is 859963392.\n";
#endif
	return 0;
}

