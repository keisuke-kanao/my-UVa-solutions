
/*
	UVa 11351 - Last Man Standing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11351_Last_Man_Standing.cpp

	This is Josephus problem (http://en.wikipedia.org/wiki/Josephus_problem).
*/

#include <iostream>
using namespace std;

int josephus(int n, int k)
{
	int r = 0;
	for (int i = 1; i <= n; i++)
		r = (r + k) % i;
	return r + 1;
}

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int n, k;
		cin >> n >> k;
		cout << "Case " << c << ": " << josephus(n, k) << endl;
	}
	return 0;
}

