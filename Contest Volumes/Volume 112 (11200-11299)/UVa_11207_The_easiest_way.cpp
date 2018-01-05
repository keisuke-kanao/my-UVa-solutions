
/*
	UVa 11207 - The easiest way

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11207_The_easiest_way.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int biggest = 0;
		double biggest_side = 0.0, w, h, s;
		for (int i = 1; i <= n; i++) {
			cin >> w >> h;
			if (w < h)
				swap(w, h);
			s = (h * 4.0 > w) ? max(h / 2.0, w / 4.0) : h;
			if (s > biggest_side) {
				biggest = i;
				biggest_side = s;
			}
		}
		cout << biggest << endl;
	}
	return 0;
}

