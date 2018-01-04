
/*
	UVa 12149 - Feynman

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_12149_Feynman.cpp

	This problem is a simpler version of UVa 10177 - (2/3/4)-D Sqr/Rects/Cubes/Boxes?.
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << n * (n + 1) * (2 * n + 1) / 6 << endl;
	}
	return 0;
}

