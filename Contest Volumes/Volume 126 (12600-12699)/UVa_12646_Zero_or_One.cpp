
/*
	UVa 12646 - Zero or One

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12646_Zero_or_One.cpp
*/

#include <iostream>
using namespace std;

/*
C B A
0 0 0
0 0 1	A
0 1 0	B
0 1 1	C
1 0 0 	C
1 0 1	B
1 1 0	A
1 1 1
*/

int main()
{
	int alice, bob, clara;
	while (cin >> alice >> bob >> clara) {
		int zero_or_ones = 0;
		if (alice)
			zero_or_ones |= 1;
		if (bob)
			zero_or_ones |= 2;
		if (clara)
			zero_or_ones |= 4;
		switch (zero_or_ones) {
		case 1: case 6:
			cout << "A\n"; break;
		case 2: case 5:
			cout << "B\n"; break;
		case 3: case 4:
			cout << "C\n"; break;
		default:
			cout << "*\n"; break;
		}
	}
	return 0;
}

