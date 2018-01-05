
/*
	UVa 10783 - Odd Sum

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10783_Odd_Sum.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int a, b;
		cin >> a >> b;
		int odd_sum = 0;
		if (!(a & 1))
			a++;
		for ( ; a <= b; a += 2)
			odd_sum += a;
		cout << "Case " << c << ": " << odd_sum << endl;
	}
	return 0;
}

