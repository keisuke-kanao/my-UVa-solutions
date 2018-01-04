
/*
	UVa 12704 - Little Masters

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12704_Little_Masters.cpp
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--) {
		double x, y, r;
		cin >> x >> y >> r;
		double d = sqrt(x * x + y * y);
		cout << fixed << setprecision(2) << r - d << ' ' << setprecision(2) << r + d << endl;
	}
	return 0;
}

