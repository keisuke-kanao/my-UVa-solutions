
/*
	UVa 948 - Fibonaccimal Base

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_948_Fibonaccimal_Base.cpp
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
using namespace std;

const int nr_fibs_max = 64;
int fibs[nr_fibs_max + 1]; // fibs[i] is the i-th fibonacci number
const int n_max = 100000000;

char* fibonaccimal_base(int n, int nf, const int* pfibs, char* base)
{
	for (int i = distance(pfibs, lower_bound(pfibs, pfibs + nf, n)); ; i--) {
		if (n == pfibs[i]) {
			base[nr_fibs_max - i - 1] = '1';
			return &base[nr_fibs_max - i - 1];
		}
		else {
			base[nr_fibs_max - i] = '1';
			if (fibonaccimal_base(n - pfibs[i - 1], i - 2, pfibs, base))
				return &base[nr_fibs_max - i];
			base[nr_fibs_max - i] = '0';
		}
	}
	return NULL;
}

int main()
{
	fibs[0] = 0; fibs[1] = 1;
	int nr_fibs;
	for (nr_fibs = 2; nr_fibs <= nr_fibs_max; nr_fibs++) {
		fibs[nr_fibs] = fibs[nr_fibs - 1] + fibs[nr_fibs - 2];
#ifdef DEBUG
		cout << nr_fibs << ' ' << fibs[nr_fibs] << endl;
#endif
		if (fibs[nr_fibs] >= n_max)
			break;
	}
	nr_fibs -= 2;
	const int* pfibs = &fibs[2]; // fibs[0] and fibs[1] will never be used
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		char base[nr_fibs_max + 1];
		memset(base, '0', nr_fibs_max);
		base[nr_fibs_max] = '\0';
		cout << n << " = " << fibonaccimal_base(n, nr_fibs, pfibs, base) << " (fib)\n";
	}
	return 0;
}

