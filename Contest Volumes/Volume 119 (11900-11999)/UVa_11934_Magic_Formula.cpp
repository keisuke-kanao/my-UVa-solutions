
/*
	UVa 11934 - Magic Formula

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11934_Magic_Formula.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int a, b, c, d, L;
		cin >> a >> b >> c >> d >> L;
		if (!a && !b && !c && !d && !L)
			break;
		int nr_divisable = 0;
		for (int i = 0; i <= L; i++)
			if (!((a * i * i + b * i + c) % d))
				nr_divisable++;
		cout << nr_divisable << endl;
	}
	return 0;
}

