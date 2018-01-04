
/*
	UVa 12342 - Tax Calculator

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12342_Tax_Calculator.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int tax_calculator(int k)
{
	int tax;
	double t;
	if (k <= 180000)
		return 0;
	k -= 180000;
	if (k <= 300000) {
		t = static_cast<int>(ceil(static_cast<double>(k) * 0.1));
		if (t < 2000)
			t = 2000;
		return t;
	}
	k -= 300000;
	tax = 30000; // 300000 * 0.10
	if (k <= 400000) {
		t = static_cast<int>(ceil(static_cast<double>(k) * 0.15));
		return tax + t;
	}
	k -= 400000;
	tax += 60000; // 400000 * 0.15
	if (k <= 300000) {
		t = static_cast<int>(ceil(static_cast<double>(k) * 0.2));
		return tax + t;
	}
	k -= 300000;
	tax += 60000; // 300000 * 0.2
	t = static_cast<int>(ceil(static_cast<double>(k) * 0.25));
	return tax + t;
}

int main()
{
	int t;
	cin >> t;
	for (int ti = 1; ti <= t; ti++) {
		int k;
		cin >> k;
		cout << "Case " << ti << ": " << tax_calculator(k) << endl;
	}
	return 0;
}

