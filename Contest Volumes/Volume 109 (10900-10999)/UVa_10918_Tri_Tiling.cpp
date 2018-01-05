
/*
	UVa 10918 - Tri Tiling

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10918_Tri_Tiling.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 30;
	int tilings[n_max + 1];
	for (int i = 0; i <= n_max; i++)
		tilings[i] = 0;
	tilings[0] = 1; tilings[2] = 3;
	for (int i = 2; i <= n_max / 2; i++) {
		tilings[2 * i] = 2;
		for (int j = 1; j < i - 1; j++)
			tilings[2 * i] += 2 * tilings[2 * j];
		tilings[2 * i] += 3 * tilings[2 * (i - 1)];
#ifdef DEBUG
		cout << "tilings[" << 2 * i << "] = " << tilings[2 * i] << endl;
#endif
	}
	while (true) {
		int n;
		cin >> n;
		if (n == -1)
			break;
		cout << tilings[n] << endl;
	}
	return 0;
}

