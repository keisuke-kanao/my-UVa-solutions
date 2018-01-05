
/*
	UVa 10880 - Colin and Ryan

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10880_Colin_and_Ryan.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

const int c_max = 44722; // sqrt(2000000000) = 44721.359549995793928183473374626
bool cookies[c_max + 1]; // cookies[i] is true if guests can eat i cookies

int main()
{
	int n;
	cin >> n;
	for (int case_nr = 1; case_nr <= n; case_nr++) {
		int c, r;
		cin >> c >> r;
		cout << "Case #" << case_nr << ':';
		c -= r;
		if (!c) {
			cout << ' ' << 0 << endl;
			continue;
		}
		int q_max = static_cast<int>(ceil(sqrt(static_cast<double>(c))));
		int printed_q_max = 0;
		for (int q = 1; q <= q_max; q++) {
			if (c % q)
				cookies[q] = false;
			else {
				cookies[q] = true;
				if (q > r) {
					cout << ' ' << q;
					printed_q_max = q;
				}
			}
		}
		for (int q = q_max; q > 0; q--)
			if (cookies[q]) {
				int pq = c / q;
				if (pq > printed_q_max && pq > r)
					cout << ' ' << pq;
			}
		cout << endl;
	}
	return 0;
}

