
/*
	UVa 11044 - Searching for Nessy

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11044_Searching_for_Nessy.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		cout << (n / 3) * (m / 3) << endl;
	}
	return 0;
}

