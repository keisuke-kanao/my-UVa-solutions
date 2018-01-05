
/*
	UVa 11313 - Gourmet Games

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11313_Gourmet_Games.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		int nr = 1, d;
		while (true) {
			if (n == m)
				break;
			else if (n < m) {
				nr = -1; break;
			}
			d = n / m;
			n = d + n % m;
			nr += d;
		}
		if (nr == -1)
			cout << "cannot do this\n";
		else
			cout << nr << endl;
	}
	return 0;
}

