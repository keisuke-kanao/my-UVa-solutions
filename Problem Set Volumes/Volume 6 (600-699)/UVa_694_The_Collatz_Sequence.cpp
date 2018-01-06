
/*
	UVa 694 - The Collatz Sequence

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_694_The_Collatz_Sequence.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	for (int c = 1; ; c++) {
		int a;
		long long l;
		cin >> a >> l;
		if (a < 0 && l < 0)
			break;
		int nr_computed = 1;
		for (int i = a; i != 1; nr_computed++) {
			if (i & 1) {
				long long r = static_cast<long long>(i) * 3 + 1;
				if (r > l)
					break;
				i = static_cast<int>(r);
			}
			else
				i >>= 1;
		}
		cout << "Case " << c << ": A = " << a << ", limit = " << l << ", number of terms = " << nr_computed << endl;
	}
	return 0;
}

