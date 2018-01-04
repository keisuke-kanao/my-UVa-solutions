
/*
	UVa 12372 - Packing for Holidays

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_12372_Packing_for_Holidays.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int lwh_max = 20;
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int l, w, h;
		cin >> l >> w >> h;
		cout << "Case " << case_nr << ((l > lwh_max || w > lwh_max || h > lwh_max) ? ": bad\n" : ": good\n");
	}
	return 0;
}

