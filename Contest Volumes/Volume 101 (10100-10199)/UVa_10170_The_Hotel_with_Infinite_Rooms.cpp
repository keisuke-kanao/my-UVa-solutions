
/*
	UVa 10170 - The Hotel with Infinite Rooms

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10170_The_Hotel_with_Infinite_Rooms.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	From Σ(S + i) (i = 0 to n) >= D,
	n = (-(2S - 1) + sqrt(4S^2 - 4S + 1 + 8D)) / 2.
	the size of the group = S + (ceil(n) - 1).
*/

int main()
{
	long long s, d;
	while (cin >> s >> d) {
		double ds  = static_cast<double>(s), dd = static_cast<double>(d);
		double dn = (-(2.0 * ds - 1.0) + sqrt(4.0 * ds * ds - 4.0 * ds + 1.0 + 8.0 * dd)) / 2.0;
		cout << s + static_cast<long long>(ceil(dn)) - 1 << endl;
	}
	return 0;
}

