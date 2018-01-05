
/*
	UVa 10931 - Parity

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10931_Parity.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int I;
		cin >> I;
		if (!I)
			break;
		int nr_parities = 0, msb = -1;
		for (int i = I, j = 0; i; i >>= 1, j++)
			if (i & 1) {
				nr_parities++;
				msb = j;
			}
		cout << "The parity of ";
		for (int b = 1 << msb; b; b >>= 1)
			cout << ((I & b) ? '1' : '0');
		cout << " is " << nr_parities << " (mod 2).\n";
	}
	return 0;
}

