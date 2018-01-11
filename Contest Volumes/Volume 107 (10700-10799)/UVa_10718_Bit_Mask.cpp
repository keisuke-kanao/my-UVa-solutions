
/*
	UVa 10718 - Bit Mask

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10718_Bit_Mask.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	unsigned int n, l, u;
	while (cin >> n >> l >> u) {
		unsigned int partial_l = 0, partial_u = 0, m = 0;
		for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
			if (l & mask)
				partial_l |= mask;
			if (u & mask)
				partial_u |= mask;
			if (n & mask) {
				if (m < partial_l)
					m |= mask;
			}
			else {
				if ((m | mask) <= partial_u)
					m |= mask;
			}
		}
		cout << m << endl;
	}
	return 0;
}

