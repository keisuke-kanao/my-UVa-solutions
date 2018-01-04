
/*
	UVa 11614 - Etruscan Warriors Never Play Chess

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11614_Etruscan_Warriors.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		long long n;
		cin >> n;
		long long r = static_cast<long long>((-1.0 + sqrt(1.0 + 8.0 * static_cast<double>(n))) / 2.0);
		cout << r << endl;
	}
	return 0;
}

