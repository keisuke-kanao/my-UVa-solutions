
/*
	UVa 580 - Critical Mass

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_580_Critical_Mass.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 30;
	int twos[n_max + 1];
/*
	twos[i] is the numuber of ways in which at most two uranium cubes are stacked consecutively out of i cubes, 
	and the last two cubes are both uranium ones.
*/
	twos[2] = 1;
	int UU = 1, UL= 0, LU = 0, LL = 0;
	for (int i = 3; i <= n_max; i++) {
		int next_UU = LU, next_UL = UU + LU, next_LU = LL + UL, next_LL = LL + UL;
		twos[i] = next_UU + next_UL + next_LU + next_LL;
#ifdef DEBUG
		cout << twos[i] << endl;
#endif
		UU = next_UU; UL = next_UL; LU = next_LU; LL = next_LL;
	}
	int threes[n_max + 1];
/*
	threes[i] is the numuber of ways in which at least three uranium cubes are stacked consecutively out of i cubes.
*/
	threes[0] = threes[1] = threes[2] = 0;
	for (int i = 3; i <= n_max; i++) {
		threes[i] = threes[i - 1] * 2 + twos[i - 1];
#ifdef DEBUG
		cout << threes[i] << endl;
#endif
	}
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		cout << threes[n] << endl;
	}
	return 0;
}

