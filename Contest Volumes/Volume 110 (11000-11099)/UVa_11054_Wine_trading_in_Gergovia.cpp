
/*
	UVa 11054 - Wine trading in Gergovia

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11054_Wine_trading_in_Gergovia.cpp

	from University of Ulm Local Contest 2006 Problem G
		(http://www.informatik.uni-ulm.de/acm/Locals/2006/html/index.html)
*/

#include <iostream>
using namespace std;

/*
	While reading a(i), calculate the following two values:
		the amount of wines (positive or negative).
		the amount of work needed so far.
*/

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		long long wine = 0, work = 0;
		for (int i = 0; i < n; i++) {
			work += (wine > 0) ? wine : -wine;
			int w;
			cin >> w;
			wine += w;
		}
		cout << work << endl;
	}
	return 0;
}

