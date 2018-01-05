
/*
	UVa 10780 - Again Prime? No Time.

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10780_Again_Prime_No_Time.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

const int m_max = 5000, n_max = 10000;
int mps[m_max + 1], nps[n_max + 1]; // mps[i], nps[i] is the number of occurrences for the prime number of i

int prime_factorization(int n, int ps[])
{
	int p_max = -1;
	for ( ; !(n & 1); n >>= 1) {
		p_max = 2;
		ps[2]++;
	}
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n)) + 1.0); i <= e; ) {
		if (!(n % i)) {
			p_max = i;
			ps[i]++;
			n /= i;
		}
		else
			i += 2;
	}
	if (n > 1) {
		p_max = n;
		ps[n]++;
	}
	return p_max;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	for (int case_nr = 1; case_nr <= nr_cases; case_nr++) {
		int m, n;
		cin >> m >> n;
		int mp_min = -1;
		if (n != 1) {
			for (int i = 2; i <= m; i++)
				mps[i] = 0;
			int mp_max = prime_factorization(m, mps);
			for (int i = 2; i <= m; i++)
				nps[i] = 0;
			for (int i = 2; i <= n; i++)
				prime_factorization(i, nps);
			for (int i = 2; i <= mp_max; i++)
				if (mps[i]) { // i is a prime factor of m
					if (nps[i] >= mps[i]) {
						int p_min = nps[i] / mps[i];
						if (mp_min == -1)
							mp_min = p_min;
						else if (p_min < mp_min)
							mp_min = p_min;
					}
					else {
						mp_min = -1;
						break;
					}
				}
		}
		cout << "Case " << case_nr << ":\n";
		if (mp_min == -1)
			cout << "Impossible to divide\n";
		else
			cout << mp_min << endl;
	}
	return 0;
}

