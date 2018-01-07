
/*
	UVa 573 - The Snail

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_573_The_Snail.cpp

	from ACM Mid Central Regionals 1997 Problem #2
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1997/index.html)
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		double h, u, d, f;
		cin >> h >> u >> d >> f;
		if (h == 0.0)
			break;
		double uf = u * f / 100.0;
		int days = 1;
		double ds = 0.0;
		while (true) {
			if (u > 0.0)
				ds += u;
			if (ds > h)
				break;
			ds -= d;
			if (ds < 0.0)
				break;
			days++;
			if (u > 0.0)
				u -= uf;
		}
		cout << ((ds >= h) ? "success on day " : "failure on day ") << days << endl;
	}
	return 0;
}

