
/*
	UVa 10014 - Simple calculations

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10014_Simple_calculations.cpp
*/

#include <iostream>
#include <cstdio>
using namespace std;

/*
	For n >= 1,
		a(1) = (n * a(0) + a(n + 1)) / (n + 1) - {Σ(n - k + 1) * c(k) (k = 1 to n)} * 2 / (n + 1).
*/

const int n_max = 3000;
double c[n_max];

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		double a0, an;
		cin >> a0 >> an;
		for (int i = 0; i < n; i++)
			cin >> c[i];
		double a1 = 0.0;
		for (int i = 0; i < n; i++)
			a1 += static_cast<double>(n - i) * c[i];
		a1 *= -2.0;
		double dn = static_cast<double>(n);
		a1 += dn * a0 + an;
		a1 /= (dn + 1.0);
		printf("%.2lf\n", a1);
		if (t)
			putchar('\n');
	}
	return 0;
}

