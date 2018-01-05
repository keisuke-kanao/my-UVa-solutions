
/*
	UVa 10994 - Simple Addition

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10994_Simple_Addition.cpp
*/

#include <iostream>
using namespace std;

long long sum_of_fn(long long n) // sum of F(n) up to n
{
	const int sums[] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
	long long s = 0;
	while (n) {
		s += (n / 10) * 45;
		s += sums[n % 10];
		n /= 10;
	}
	return s;
}

int main()
{
	while (true) {
		int p, q;
		cin >> p >> q;
		if (p < 0 && q < 0)
			break;
		long long s = sum_of_fn(q);
		if (p)
			s -= sum_of_fn(p - 1);
		cout << s << endl;
	}
	return 0;
}

