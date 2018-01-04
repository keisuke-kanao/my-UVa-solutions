
/*
	UVa 11650 - Mirror Clock

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11650_Mirror_Clock.cpp
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int h, m;
		char c;
		cin >> h >> c >> m;
		if (!m && !(h % 6)) {
			if (!h)
				h = 12;
		}
		else {
			if (m) {
				m = 60 - m;
				h = 11 - h;
			}
			else
				h = 12 - h;
			if (h <= 0)
				h += 12;
		}
		cout << setfill('0') << setw(2) << h << c << setw(2) << m << endl;
	}
	return 0;
}

