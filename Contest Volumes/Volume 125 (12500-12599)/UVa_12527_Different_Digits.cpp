
/*
	UVa 12527 - Different Digits

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12527_Different_Digits.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_max = 5000;
int numbers[nr_max]; // numbers that don't have repeated digits

bool different_digits(int n)
{
	int d, digits = 0; // bit i is 1 if n has digit i (0 <= i <= 9)
	do {
		d = 1 << (n % 10);
		if (digits & d)
			return false;
		digits |= d;
		n /= 10;
	} while (n);
	return true;
}

int main()
{
	int n, m, nr = 0;
	for (n = 1; n <= nr_max; n++)
		if (different_digits(n))
			numbers[nr++] = n;
	numbers[n++] = 5012; // sentinel
#ifdef DEBUG
	cout << nr << endl;
#endif
	while (cin >> n >> m) {
		int ni = distance(numbers, lower_bound(numbers, numbers + nr, n));
		int mi = distance(numbers, lower_bound(numbers, numbers + nr, m));
		if (m == numbers[mi])
			mi++;
		cout << mi - ni << endl;
	}
	return 0;
}

