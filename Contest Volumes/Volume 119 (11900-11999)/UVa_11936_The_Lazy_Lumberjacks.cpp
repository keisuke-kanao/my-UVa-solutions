
/*
	UVa 11936 - The Lazy Lumberjacks

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11936_The_Lazy_Lumberjacks.cpp

	This problem is similar to UVa 11479 - Is this the easiest problem?.
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int a, b, c;
		cin >> a >> b >> c;
		cout << ((a <= 0 || b <= 0 || c <= 0 || a + b <= c || b + c <= a || c + a <= b) ? "Wrong!!\n" : "OK\n");
	}
	return 0;
}

