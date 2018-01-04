
/*
	UVa 440 - Eeny Meeny Moo

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_440_Eeny_Meeny_Moo.cpp

	This is exactly the same problem as 151 - Power Crisis, except for the last number.

	from University of Ulm Local Contest 1996 Problem E
		(http://www.informatik.uni-ulm.de/acm/Locals/1996/)
*/

#include <iostream>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int get_random_number(int n)
{
	const int n_max = 150;
	bool turned_offs[n_max + 1];
	for (int m = 1; ; m++) {
		int nr_turned_offs = 0;
		memset(turned_offs, 0, sizeof(turned_offs));
		int i = 1;
		while (true) {
#ifdef DEBUG
			cout << i << ' ';
#endif
			turned_offs[i] = true;
			if (++nr_turned_offs == n) {
#ifdef DEBUG
				cout << endl;
#endif
				if (i == 2)
					return m;
				else
					break;
			}
			int j = m;
			while (true) {
				if (++i > n)
					i = 1;
				if (!turned_offs[i] && !--j)
					break;
			}
		}
	}
}

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
		cout << get_random_number(n) << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

