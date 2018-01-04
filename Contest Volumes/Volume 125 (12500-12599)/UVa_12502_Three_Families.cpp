
/*
	UVa 12502 - Three Families

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_12502_Three_Families.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int x, y, z;
		cin >> x >> y >> z;
		cout << (2 * x - y) * z / (x + y) << endl;
	}
	return 0;
}

