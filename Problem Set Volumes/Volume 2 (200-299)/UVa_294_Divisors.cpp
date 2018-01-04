
/*
	UVa 294 - Divisors

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_294_Divisors.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	If the number is a^i * b^j * c^k * ..., then it has (i + 1) * (j+1) * (k+1)... divisors.
*/

int number_of_divisors(int n)
{
	if (n < 3)
		return n;
	int nr = 2; // 1 and n
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n))); i <= e; i++)
		if (!(n % i)) {
			nr++;
			int j = n / i;
			if (j > i)
				nr++;
		}
	return nr;
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int l, u;
		cin >> l >> u;
		int p, max_nr_divisors = 0;
		for (int i = l; i <= u; i++) {
			int nr_divisors = number_of_divisors(i);
			if (nr_divisors > max_nr_divisors) {
				p = i;
				max_nr_divisors = nr_divisors;
			}
		}
		cout << "Between " << l << " and " << u <<", " << p << " has a maximum of " << max_nr_divisors << " divisors.\n";
	}
	return 0;
}

