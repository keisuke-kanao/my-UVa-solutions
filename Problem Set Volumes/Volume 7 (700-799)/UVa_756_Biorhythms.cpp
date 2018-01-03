
/*
	UVa 756 - Biorhythms

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_756_Biorhythms.cpp

	from ACM East Central Regionals 1999 Problem F
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_EastCen/1999/index.html)
*/

#include <iostream>
using namespace std;

int main()
{
	const int p_cycle = 23, e_cycle = 28, i_cycle = 33, d_max = 21252;
	for (int cn = 1; ; cn++) {
		int p, e, i, d;
		cin >> p >> e >> i >> d;
		if (p == -1 && e == -1 && i == -1 && d == -1)
			break;
		int di;
		for (di = i + i_cycle; ; di += i_cycle)
			if (di > d &&
				di > e && !((di - e) % e_cycle) &&
				di > p && !((di - p) % p_cycle))
				break;
		di -= d;
		if (di > d_max)
			di %= d_max;
		cout << "Case " << cn << ": the next triple peak occurs in " << di << " days.\n";
	}
	return 0;
}

