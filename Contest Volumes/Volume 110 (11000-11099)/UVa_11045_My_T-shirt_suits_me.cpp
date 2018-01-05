
/*
	UVa 11045 - My T-shirt suits me

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11045_My_T-shirt_suits_me.cpp
*/

#include <iostream>
#include <string>
using namespace std;

const int nr_s = 6, m_max = 30;
enum {s_xxl = 0x20, s_xl = 0x10, s_l = 0x08, s_m = 0x04, s_s = 0x02, s_xs = 0x01};
int remainings[nr_s];
	// remainings[i] is the number of remainings for the T-shirt of each size.
int two_sizes[m_max];
	// two_sizes[i] is the sizes of i-th volunteer
int distributions[m_max];
	// distributions[i] is the distributions of T-shirts for i-th or later volunteers

bool distribute_shirts(int i, int m, int d)
{
	if (i == m)
		return true;
	else if ((d & distributions[i]) == d) {
		int ts = two_sizes[i];
		for (int j = 0, b = 1; j < nr_s; j++, b <<= 1)
			if (ts & b && remainings[j]) {
				if (!--remainings[j])
					d &= ~b;
				if (distribute_shirts(i + 1, m, d))
					return true;
				if (!remainings[j]++)
					d |= b;
			}
		return false;
	}
	else
		return false;
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		int i, j, r, d;
		for (i = 0, r = n / nr_s; i < nr_s; i++)
			remainings[i] = r;
		for (i = 0; i < m; i++) {
			d = 0;
			for (j = 0; j < 2; j++) {
				string s;
				cin >> s;
				if (s == "XXL")
					d |= s_xxl;
				else if (s == "XL")
					d |= s_xl;
				else if (s == "L")
					d |= s_l;
				else if (s == "M")
					d |= s_m;
				else if (s == "S")
					d |= s_s;
				else // "XS"
					d |= s_xs;
			}
			two_sizes[i] = d;
		}
		for (int i = m - 1, d = 0; i >= 0; i--) {
			d |= two_sizes[i];
			distributions[i] = d;
		}
		cout << ((distribute_shirts(0, m, d)) ? "YES\n" : "NO\n");
	}
	return 0;
}

