
/*
	UVa 11428 - Cubes

	To build using Visual Studio 2008:
		cl -EHsc -O2 -DONLINE_JUDGE UVa_11428_Cubes.cpp
*/

#include <iostream>
#include <limits>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		long long x, y;
#ifdef ONLINE_JUDGE
		for (y = 1; ; y++) {
#else
		for (y = 0; ; y++) {
#endif
			long long m = y * y * y + n;
			x = static_cast<int>(pow(static_cast<double>(m) /* + numeric_limits<float>::epsilon() */, 1.0 / 3.0));
			if ((x + 1) * (x + 1) * (x + 1) == m)
				x++;
			if (x == y) {
				x = -1;
				break;
			}
			else if (x * x * x == m)
				break;
		}
		if (x != -1)
			cout << x << ' ' << y << endl;
		else
			cout << "No solution\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

