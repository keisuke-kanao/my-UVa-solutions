
/*
	UVa 10970 - Big Chocolate

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10970_Big_Chocolate.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int m, n;
	while (cin >> m >> n)
		cout << m * n - 1 << endl;
	return 0;
}

