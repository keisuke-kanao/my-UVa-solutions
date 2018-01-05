
/*
	UVa 10235 - Simply Emirp

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10235_Simply_Emirp.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(int n)
{
	if (n == 1)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

int reverse_digits(int n)
{
	int r = 0;
	for ( ; n; n /= 10) {
		if (r)
			r *= 10;
		r += n % 10;
	}
	return r;
}

int main()
{
	int n;
	while (cin >> n) {
		if (!is_prime(n))
			cout << n << " is not prime.\n";
		else {
			int r = reverse_digits(n);
			if (r != n && is_prime(r))
				cout << n << " is emirp.\n";
			else
				cout << n << " is prime.\n";
		}
	}
	return 0;
}

