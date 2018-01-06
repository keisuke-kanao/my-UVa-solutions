
/*
	UVa 10079 - Pizza Cutting

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10079_Pizza_Cutting.cpp
*/

/*
Let c(n) be the number of cuts for n lines, then:
	c(0) = 1
	c(n + 1) = c(n) + n
*/

#include <iostream>
using namespace std;

int main()
{
	while (true) {
		long long n;
		cin >> n;
		if (n < 0)
			break;
		cout << n * (n + 1) / 2 + 1 << endl;
	}
	return 0;
}

