
/*
	UVa 679 - Dropping Balls

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_679_Dropping_Balls.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int D, I;
		cin >> D >> I;
		int P = 1 << (D - 1), pd = 1 << (D - 2);
		while (I > 1) {
			if (!(I & 1)) {
				P += pd;
				I >>= 1;
			}
			else
				I = (I + 1) / 2;
			pd >>= 1;
		}
		cout << P << endl;
	}
	cin >> t;
	return 0;
}

