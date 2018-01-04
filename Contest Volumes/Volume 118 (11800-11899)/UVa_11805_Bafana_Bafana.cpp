
/*
	UVa 11805 - Bafana Bafana

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11805_Bafana_Bafana.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int n, k, p;
		cin >> n >> k >> p;
		int i = (k - 1 + p) % n + 1;
		cout << "Case " << c << ": " << i << endl;
	}
	return 0;
}

