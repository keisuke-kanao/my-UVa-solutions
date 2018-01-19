
/*
	7.6.3 Euclid Problem
	PC/UVa IDs: 110703/10104, Popularity: A, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10104_Euclid_Problem.cpp
*/

#include <iostream>
#include <cassert>
using namespace std;

// find the gcd(a,b) and x,y such that a * x + b * y = gcd(a,b)

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

int main(int /* argc */, char** /* argv */)
{
	int a, b;
	while (cin >> a >> b) {
		int x, y;
		int d = gcd(a, b, x, y);
/*
		if (x > y) {
			if (!y) {
				assert(x == 1);
				y = x;
				x = (d - b * y) / a;
			}
			else {
				x = -x; y = -y;
			}
		}
*/
		cout << x << ' ' << y << ' ' << d << endl;
	}
	return 0;
}

