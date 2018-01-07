
/*
	UVa 10790 - How Many Points of Intersection?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10790_How_Many_Points_of_Intersection.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	for (int c = 1; ; c++) {
		long long a, b;
		cin >> a >> b;
		if (!a && !b)
			break;
		cout << "Case " << c << ": " << a * (a - 1) * b * (b - 1) / 4 << endl;
	}
	return 0;
}

