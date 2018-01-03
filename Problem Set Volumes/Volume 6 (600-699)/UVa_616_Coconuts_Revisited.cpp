
/*
	UVa 616 - Coconuts, Revisited

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_616_Coconuts_Revisited.cpp

	from ACM ICPC North Central Regionals 1997 Problem 3
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1997/index.html)
*/

#include <iostream>
#include <algorithm>
using namespace std;

/*
	Number of coconuts = (1 + n * k) * n^n  - (n - 1) for n odd
	  				   = (n - 1 + n * k) * n^n - (n - 1) for n even
*/

#include <iostream>
#include <cmath>
using namespace std;

const int n_max = 11;
long long pow_ns[n_max + 1]; // pow_ns[i] is pow(i, i)
long long min_coconuts[n_max + 1]; // min_coconuts[i] is the minimum number of coconuts for i

bool monkey_coconuts(long long c, int n)
{
	c += n - 1;
	if (c % pow_ns[n])
		return false;
	c /= pow_ns[n];
	if (n & 1)
		c--;
	else
		c -= n - 1;
	return (c % n) ? false : true;
}

int main()
{
	for (int i = 2; i <= n_max; i++) {
		pow_ns[i] = static_cast<long long>(pow(static_cast<double>(i), static_cast<double>(i)));
		if (i & 1)
			min_coconuts[i] = pow_ns[i] - (i - 1);
		else
			min_coconuts[i] = pow_ns[i] * (i - 1) - (i - 1);
#ifdef DEBUG
		cout << min_coconuts[i] << endl;
#endif
	}
	while (true) {
		long long c;
		cin >> c;
		if (c < 0)
			break;
		int n;
		for (n = 2; n <= n_max; n++)
			if (c < min_coconuts[n])
				break;
		for ( ; n > 1; n--)
			if (monkey_coconuts(c, n))
				break;
		cout << c << " coconuts, ";
		if (n == 1)
			cout << "no solution\n";
		else
			cout << n << " people and 1 monkey\n";
	}
	return 0;
}
