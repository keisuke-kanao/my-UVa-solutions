
/*
	UVa 11388 - GCD LCM

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11388_GCD_LCM.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int g, l;
		cin >> g >> l;
		if (l % g)
			cout << -1 << endl;
		else
			cout << g << ' ' << l << endl;
	}
	return 0;
}

