
/*
	UVa 594 - One Little, Two Little, Three Little Endians

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_594_Little_Endians.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		int m = 0;
		for (int i = 0, j = n; i < 4; i++, j >>= 8) {
			m <<= 8;
			m |= j & 0xff;
		}
		cout << n << " converts to " << m << endl;
	}
	return 0;
}

