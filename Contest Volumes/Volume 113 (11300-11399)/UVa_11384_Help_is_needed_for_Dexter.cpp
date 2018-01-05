
/*
	UVa 11384 - Help is needed for Dexter

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11384_Help_is_needed_for_Dexter.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	const double log2 = log(2.0);
	int n;
	while (cin >> n)
		cout << static_cast<int>(log(static_cast<double>(n)) / log2) + 1 << endl; // log2(n) + 1
	return 0;
}

