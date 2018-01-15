
/*
	UVa 10277 - Boastin' Red Socks

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10277_Boastin_Red_Socks.cpp

	from Waterloo ACM Programming Contest June 19, 1999 Problem E
		(http://plg1.cs.uwaterloo.ca/~acm00/990619/)

	An accepted solution.
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	Let r be the number of red socks and s be the number of all socks, then:
		C(r, 2) / C(s, 2) = p / q.
		r * (r - 1) = k * p, s * (s -  1) = k * q.
*/

long long calculate_gcd(long long a, long long b)
{
	if (a < b)
		return calculate_gcd(b, a);
	if (!b)
		return a;
	else
		return calculate_gcd(b, a % b);
}

long long solve_quadratic_equation(long long n, long long n_max)
{
	long long i = static_cast<long long>((1.0 + sqrt(1.0 + 4.0 * static_cast<double>(n))) / 2.0);
	return (i <= n_max && i * i - i - n == 0) ? i : - 1;
}

int main()
{
	const long long nr_socks_max = 50000;
	while (true) {
		long long p, q;
		cin >> p >> q;
		if (!p && !q)
			break;
		long long r = -1, s;
		if (!p) {
			r = 0; s = 2; // just a couple of black socks
		}
		else if (p == q)
			r = s = 2; // just a couple of red socks
		else {
			long long gcd = calculate_gcd(p, q);
			p /= gcd; q /= gcd;
			for (s = 3; s <= nr_socks_max; s++) {
				long long t = s * (s - 1);
				if (!(t % q)) {
					long long k = t / q;
					if ((r = solve_quadratic_equation(k * p, s)) != -1)
						break;
				}
			}
		}
		if (r != -1)
			cout << r << ' ' << s - r << endl;
		else
			cout << "impossible\n";
	}
	return 0;
}

