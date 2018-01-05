
/*
	UVa 10489 - Boxes of Chocolates

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10489_Boxes_of_Chocolates.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, b;
		cin >> n >> b;
		int residue = 0;
		while (b--) {
			int k;
			cin >> k;
			int r = 1;
			while (k--) {
				int a;
				cin >> a;
				r *= a;
				r %= n;
			}
			residue += r;
			residue %= n;
		}
		cout << residue << endl;
	}
	return 0;
}

