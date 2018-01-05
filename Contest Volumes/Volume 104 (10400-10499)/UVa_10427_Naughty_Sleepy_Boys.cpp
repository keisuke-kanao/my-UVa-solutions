
/*
	UVa 10427 - Naughty Sleepy Boys

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10427_Naughty_Sleepy_Boys.cpp
*/

/*
nr_digits[i]		number of digits	value
--------------------------------------------------------
9					1					1	-        9
189					2				   10	-       99
2889				3				  100	-      999
38889				4				 1000	-     9999
488889				5				10000	-    99999
5888889				6			   100000	-   999999
68888889			7			  1000000	-  9999999
788888889			8			 10000000	- 99999999

N = 10000

10000 - 2889 = 7111
(7111 + 3) / 4 = 1778
(1000 - 1) + 1778 = 2777
7111 % 4 = 3		-> 3rd digit of 2777 --> 7

N = 50000

50000 - 38889 = 11111
(11111 + 4) / 5 = 2223
(10000 - 1) + 2223 = 12222
11111 % 5 = 1		-> 1st digit of 12222 --> 1
*/

#include <iostream>
using namespace std;

int main()
{
	const int i_max = 10;
	int power_of_10[i_max + 1];
	long long nr_digits[i_max + 1];
	nr_digits[0] = 0;
	for (int i = 1, p = 1; i <= i_max; i++, p *= 10) {
		power_of_10[i] = p;
		nr_digits[i] = nr_digits[i - 1] + static_cast<long long>(i) * 9 * p;
#ifdef DEBUG
		cout << power_of_10[i] << ' ' << nr_digits[i] << endl;
#endif
	}
	long long n;
	while (cin >> n) {
		int i = 1;
		while (i <= i_max && n > nr_digits[i])
			i++;
		long long j = n - nr_digits[i - 1];
		long long m = static_cast<long long>(power_of_10[i] - 1) + (j + i - 1) / i;
		if (j % i) {
			for (int k = i - static_cast<int>(j % i); k; k--)
				m /= 10;
		}
		cout << m % 10 << endl;
	}
	return 0;
}

