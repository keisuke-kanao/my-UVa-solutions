
/*
	UVa 10673 - Play with Floor and Ceil

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10673_Play_with_Floor_and_Ceil.cpp
*/

/*
	Linear Diophantine equations take the form ax + by = c. 

	If c is the greatest common divisor of a and b then this is Bezout's identity, 
	and the equation has an infinite number of solutions. 
	These can be found by applying the extended Euclidean algorithm. 

	It follows that there are also infinite solutions 
	if c is a multiple of the greatest common divisor of a and b. 

	If c is not a multiple of the greatest common divisor of a and b, 
	then the Diophantine equation ax + by = c has no solutions.
*/

#include <iostream>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
using namespace std;

// calculate gcd(a, b) and x, y such that a * x + b * y = gcd(a,b)

int gcd(int a, int b, int& x, int& y)
{
	if (b > a)
		return gcd(b, a, y, x);
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	int x1, y1;
	int d = gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return d;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int x, k;
		cin >> x >> k;
		int f = x / k, c = x / k;
		if (x % k)
			c++;
		int u, v;
		int d = gcd(f, c, u, v);
#ifndef ONLINE_JUDGE
		assert(u * (x / d) * f + v * (x / d) * c == x);
#endif
		cout << u * (x / d) << ' ' << v * (x / d) << endl;
	}
	return 0;
}

