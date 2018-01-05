
/*
	UVa 10963 - The Swallowing Ground

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10963_The_Swallowing_Ground.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int w;
		cin >> w;
		bool yes = true;
		for (int i = 0, gap = 0; i < w; i++) {
			int y1, y2;
			cin >> y1 >> y2;
			int g = y1 - y2;
			if (!i)
				gap = g;
			else if (yes) {
				if (gap != g)
					yes = false;
			}
		}
		cout << ((yes) ? "yes\n" : "no\n");
		if (t)
			cout << endl;
	}
	return 0;
}

