
/*
	UVa 11173 - Grey Codes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11173_Grey_Codes.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	while (N--) {
		int n, k;
		cin >> n >> k;
		int i = 0, b = 1 << (n - 1);
		bool upper_half = false;
		if (k & b) {
			i = b; upper_half = true;
		}
		for (b >>= 1; b; b >>= 1) {
			if (k & b) {
				if (!upper_half)
					i |= b;
				upper_half = true;
			}
			else {
				if (upper_half)
					i |= b;
				upper_half = false;
			}
		}
		cout << i << endl;
	}
	return 0;
}

