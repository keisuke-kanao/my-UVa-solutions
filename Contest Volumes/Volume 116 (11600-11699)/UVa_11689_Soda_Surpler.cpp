
/*
	UVa 11689 - Soda Surpler

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11689_Soda_Surpler.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int e, f, c;
		cin >> e >> f >> c;
		int nr_drunk = 0;
		e += f;
		while (e >= c) {
			int d = e / c;
			e %= c;
			e += d;
			nr_drunk += d;
		}
		cout << nr_drunk << endl;
	}
	return 0;
}

