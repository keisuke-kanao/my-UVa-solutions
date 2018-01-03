
/*
	UVa 530 - Binomial Showdown

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_530_Binomial_Showdown.cpp

	from University of Ulm Local Contest 1997 Problem B
		(http://www.informatik.uni-ulm.de/acm/Locals/1997/)
*/

#include <iostream>
using namespace std;

/*
int combination(int n, int k)
{
	return (!k || n == k) ? 1 : combination(n - 1, k - 1) + combination(n - 1, k);
}
*/

long long combination(int n, int m)
{
	long long c = 1, d = 1;
	int k= (m > n - m) ? m : n - m;
	for (int j = 1, i = k + 1; i <= n; i++, j++) {
		c *= i;
		d *= j;
		if(!(c % d) && d != 1) {
			c /= d;
			d = 1;
		}
	}
	return c;
}

int main()
{
	while (true) {
		int n, k;
		cin >> n >> k;
		if (!n && !k)
			break;
/*
		if (n == k || !k)
			cout << 1 << endl;
		else if (k == 1)
			cout << n << endl;
		else
*/
			cout << combination(n, k) << endl;
	}
	return 0;
}

