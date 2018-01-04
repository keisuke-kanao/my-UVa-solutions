
/*
	UVa 12024 - Hats

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12024_Hats.cpp

	This problem is similar to UVa 10497 - Sweet Child Makes Trouble.
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 12;
	int factorials[n_max + 1], derangement_nrs[n_max + 1];
	factorials[0] = factorials[1] = 1;
	derangement_nrs[0] = 1; derangement_nrs[1] = 0;
	for (int i = 2; i <= n_max; i++) {
		factorials[i] = factorials[i - 1] * i;
		derangement_nrs[i] = (i - 1) * (derangement_nrs[i - 1] + derangement_nrs[i - 2]);
#ifdef DEBUG
		cout << i << ": " << factorials[i] << ' ' << derangement_nrs[i] << endl;
#endif
	}
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		cout << derangement_nrs[n] << '/' << factorials[n] << endl;
	}
	return 0;
}

