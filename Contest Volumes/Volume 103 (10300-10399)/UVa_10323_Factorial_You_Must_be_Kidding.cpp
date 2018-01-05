
/*
	UVa 10323 - Factorial! You Must be Kidding!!!

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10323_Factorial_You_Must_be_Kidding.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const long long lower_limit = 10000, upper_limit = 6227020800 /* 13! */;
	int n_min, n_max = -1;
	const int nr_factorials_max = 16;
	long long factorials[nr_factorials_max];
	factorials[0] = 1;
	for (int i = 1;  ; i++) {
		factorials[i] = i * factorials[i - 1];
#ifdef DEBUG
		cout << i << ' ' << factorials[i] << endl;
#endif
		if (factorials[i] < lower_limit)
			n_min = i + 1;
		if (factorials[i] > upper_limit) {
			n_max = i - 1;
			break;
		}
	}
	int n;
	while (cin >> n) {
		if (n < 0)
			cout << ((n & 1) ? "Overflow!\n" : "Underflow!\n");
		else if (n < n_min)
			cout << "Underflow!\n";
		else if (n > n_max)
			cout << "Overflow!\n";
		else
			cout << factorials[n] << endl;
	}
	return 0;
}

