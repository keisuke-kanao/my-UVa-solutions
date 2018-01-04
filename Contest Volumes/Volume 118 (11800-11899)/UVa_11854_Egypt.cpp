
/*
	UVa 11854 - Egypt

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11854_Egypt.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int a, b, c;
		cin >> a >> b >> c;
		if (!a && !b && !c)
			break;
		int sa = a * a, sb = b * b, sc = c * c;
		cout << ((sa + sb == sc || sb + sc == sa || sc + sa == sb) ? "right\n" : "wrong\n");
	}
	return 0;
}

