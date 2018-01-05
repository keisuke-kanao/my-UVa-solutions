
/*
	UVa 10469 - To Carry or not to Carry

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10469_To_Carry_or_not_to_Carry.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	unsigned int i, j;
	while (cin >> i >> j)
		cout << (i ^ j) << endl;
	return 0;
}

