
/*
	UVa 10791 - Minimum Sum LCM

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10791_Minimum_Sum_LCM.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	Do integer factorization (or prime factorization) for a positive integer N.
	Along the way, add the integers whose LCM is N.
*/
long long minimum_sum_lcm(int n)
{
	long long msl = 0;
	int i = 1;
	while (!(n & 1)) { // see if n is even
		i <<= 1;
		n >>= 1;
	}
	if (i > 1)
		msl = i;
	i = 1;
	for (int j = 3, k = static_cast<int>(sqrt(static_cast<double>(n)) + 1.0); j <= k; ) {
		if (!(n % j)) {
			i *= j;
			n /= j;
		}
		else {
			if (i > 1)
				msl += i;
			i = 1;
			j += 2;
		}
	}
	if (i > 1)
		msl += i;
	if (n > 1)
		msl += n;
	return msl;
}

int main()
{
	for (int c = 1; ; c++) {
		int n;
		cin >> n;
		if (!n)
			break;
		long long msl = (n == 1) ? 2 : minimum_sum_lcm(n);
		if (msl == n) // n is a prime
			msl++; // minimum sum LCM should be at least two integers and in this case, 1 is the one.
		cout << "Case " << c << ": " << msl << endl;
	}
	return 0;
}

