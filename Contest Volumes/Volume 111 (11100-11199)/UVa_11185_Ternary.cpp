
/*
	UVa 11185 - Ternary

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11185_Ternary.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (n < 0)
			break;
		int m = 1;
		while (m <= n)
			m *= 3;
		for (m /= 3; m > 1; m /= 3) {
			int i = n / m;
			cout << i;
			n -= i * m;
		}
		cout << n << endl;
	}
	return 0;
}

