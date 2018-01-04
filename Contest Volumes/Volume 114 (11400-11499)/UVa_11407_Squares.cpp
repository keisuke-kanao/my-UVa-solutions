
/*
	UVa 11407 - Squares

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11407_Squares.cpp
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
	const int N_max = 10000;
	int min_ns[N_max + 1];
	min_ns[0] = 0; min_ns[1] = 1;
	for (int i = 2; i <= N_max; i++) {
		int j = static_cast<int>(sqrt(static_cast<double>(i)));
		min_ns[i] = 1 + min_ns[i - j * j];
		if (min_ns[i] > 1)
			for (j--; j > 0; j--)
				min_ns[i] = min(min_ns[i], 1 + min_ns[i - j * j]);
	}
	int t;
	cin >> t;
	while (t--) {
		int N;
		cin >> N;
		cout << min_ns[N] << endl;
	}
	return 0;
}

