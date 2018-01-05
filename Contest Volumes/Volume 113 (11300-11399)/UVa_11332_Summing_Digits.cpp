
/*
	UVa 11332 - Summing Digits

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11332_Summing_Digits.cpp
*/

#include <iostream>
using namespace std;

int f(int n)
{
	int f = 0;
	for ( ; n; n /= 10)
		f += n % 10;
	return f;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		while (n >= 10)
			n = f(n);
		cout << n << endl;
	}
	return 0;
}

