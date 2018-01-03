
/*
	UVa 583 - Prime Factors

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_583_Prime_Factors.cpp
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

void prime_factorization(int n)
{
	bool printed = false;
	if (n < 0) {
		printed = true;
		cout << -1;
		n = abs(n);
	}

	for ( ; !(n & 1); n >>= 1) {
		if (printed)
			cout << " x 2";
		else {
			printed = true;
			cout << 2;
		}
	}
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n)) + 1.0); i <= e; ) {
		if (!(n % i)) {
			if (printed)
				cout << " x ";
			else
				printed = true;
				cout << i;
			n /= i;
		}
		else
			i += 2;
	}
	if (n > 1) {
		if (printed)
			cout << " x ";
		cout << n;
	}
	cout << endl;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << n << " = ";
		prime_factorization(n);
	}
	return 0;
}

