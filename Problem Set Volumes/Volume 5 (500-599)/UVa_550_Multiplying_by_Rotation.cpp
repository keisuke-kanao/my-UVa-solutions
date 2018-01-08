
/*
	UVa 550 - Multiplying by Rotation

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_550_Multiplying_by_Rotation.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int base, first_factor, multiplier;
	while (cin >> base >> first_factor >> multiplier) {
		int n = 0, multiplicand = first_factor;
		for (int carry = 0; ; n++) {
			int product = multiplicand * multiplier + carry;
			carry = product / base;
			if (!carry && product == first_factor)
				break;
			multiplicand = product % base;
		}
		cout << n + 1 << endl;
	}
	return 0;
}

