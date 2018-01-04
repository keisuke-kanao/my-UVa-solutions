
/*
	UVa 11461 - Square Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11461_Square_Numbers.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	while (true) {
		int a, b;
		cin >> a >> b;
		if (!a && !b)
			break;
		int sa = static_cast<int>(sqrt(static_cast<double>(a))),
			sb = static_cast<int>(sqrt(static_cast<double>(b)));
		while (sa * sa < a)
			sa++;
		while (sb * sb <= b)
			sb++;
		cout << sb - sa << endl;
	}
	return 0;
}

