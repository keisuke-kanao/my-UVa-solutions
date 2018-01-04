
/*
	UVa 11597 - Spanning Subtree

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11597_Spanning_Subtree.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		// number of spanning subtree = C(n, 2) / (n - 1) = n / 2
		cout << "Case " << case_nr << ": " << n / 2 << endl;
	}
	return 0;
}

