
/*
	UVa 568 - Just the Facts

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_568_Just_the_Facts.cpp

	An accepted solution.
*/

#include <iostream>
#include <iomanip>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int n;
	while (cin >> n) {
		unsigned long long f = 1;
		for(int i = 2; i <= n; i++) {
			f *= i;
			while (!(f % 10))
				f /= 10;
			f %= 1000000; // 100000
		}
		cout << setw(5) << setfill(' ') << n << " -> " << f % 10 << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

