
/*
	UVa 10642 - Can You Solve It?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10642_Can_You_Solve_It.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

long long calculate_steps(long long x, long long y)
{
	return (x + y) * (x + y + 1) / 2 + x;
}

int main()
{
	int n;
	cin >> n;
	for (int case_nr = 1; case_nr <= n; case_nr++) {
		long long sx, sy, dx, dy;
		cin >> sx >> sy >> dx >> dy;
		cout << "Case " << case_nr << ": " << calculate_steps(dx, dy) - calculate_steps(sx, sy) << endl;
	}
	return 0;
}

