
/*
	UVa 10346 - Peter's Smokes

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10346_Peters_Smokes.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int n, k;
	while (cin >> n >> k) {
		int nr_smokes = 0;
		while (n >= k) {
			n -= k - 1;
			nr_smokes += k;
		}
		cout << nr_smokes + n << endl;
	}
	return 0;
}

