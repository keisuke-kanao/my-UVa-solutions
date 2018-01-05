
/*
	UVa 11172 - Relational Operator

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11172_Relational_Operator.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int a, b;
		cin >> a >> b;
		if (a > b)
			cout << ">\n";
		else if (a < b)
			cout << "<\n";
		else
			cout << "=\n";
	}
	return 0;
}

