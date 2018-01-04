
/*
	UVa 471 - Magic Numbers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_471_Magic_Numbers.cpp
*/

#include <iostream>
using namespace std;
 
bool is_digits_repeated(long long n)
{
	unsigned int digits = 0; // i-th bit is '1' if digit of i (0 - 9) exists in n
	do {
		int d = 1 << static_cast<int>(n % 10);
		if (digits & d)
			return true;
		n /= 10;
		digits |= d;
	} while (n);
	return false;
}

int main()
{
	const long long s1_max = 9876543210LL;
	int t;
	cin >> t;
	while (t--) {
		long long N;
		cin >> N;
		for (long long s2 = 1, s2_max = s1_max / N; s2 <= s2_max; s2++)
			if (!is_digits_repeated(s2)) {
				long long s1 = s2 * N;
				if (!is_digits_repeated(s1))
					cout << s1 << " / " << s2 << " = " << N << endl;
			}
		if (t)
			cout << endl;
	}
	return 0;
}

