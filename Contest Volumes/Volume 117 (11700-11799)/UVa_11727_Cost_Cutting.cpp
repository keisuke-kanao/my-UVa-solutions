
/*
	UVa 11727 - Cost Cutting

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11727_Cost_Cutting.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int i, j, k, s;
		cin >> i >> j >> k;
		if (i > j) {
			if (j > k)
				s = j;
			else if (i > k)
				s = k;
			else
				s = i;
		}
		else {
			if (i > k)
				s = i;
			else if (j > k)
				s = k;
			else
				s = j;
		}
		cout << "Case " << c << ": " << s << endl;
	}
	return 0;
}

